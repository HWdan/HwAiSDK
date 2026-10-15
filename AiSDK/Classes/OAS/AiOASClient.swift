import Foundation
import OAS

private func oaError(_ code: Int, _ message: String) -> NSError {
    return NSError(domain: "AiOAS", code: code,
                   userInfo: [NSLocalizedDescriptionKey: message, "OASCode": code])
}

/// Configure before AiSDK.setDeviceInfo. All callbacks arrive on the main queue.
@objcMembers public final class AiOASClient: NSObject {
    public static let shared = AiOASClient()
    private var channelId = ""
    private var appKey = ""
    private var appUuid = ""
    private var appChannel = ""
    private var deviceId = ""
    private var resolution = ""
    private var language = "en-US"
    private var ready = false
    private var initializing = false
    private var revision = 0
    private var retryCount = 0
    private var initializationCallbacks: [(NSError?) -> Void] = []
    fileprivate var active: [UUID: AiOASRequest] = [:]

    @objc(configureWithChannelId:appKey:appUuid:appChannel:)
    public func configure(channelId: String, appKey: String,
                          appUuid: String?, appChannel: String?) {
        DispatchQueue.main.async {
            self.cancelAllOnMain()
            self.channelId = channelId
            self.appKey = appKey
            self.appUuid = appUuid ?? ""
            self.appChannel = appChannel ?? ""
            self.ready = false
            self.revision += 1
            self.retryCount = 0
            if !self.deviceId.isEmpty { self.beginInitialization() }
        }
    }

    @objc(initializeDevice:resolution:language:completion:)
    public func initializeDevice(_ deviceId: String, resolution: String, language: String,
                                 completion: @escaping (NSError?) -> Void) {
        DispatchQueue.main.async {
            if self.deviceId != deviceId || self.resolution != resolution || self.language != language {
                self.cancelAllOnMain()
                self.deviceId = deviceId
                self.resolution = resolution
                self.language = language
                self.ready = false
                self.revision += 1
                self.retryCount = 0
            }
            if self.ready { completion(nil); return }
            self.initializationCallbacks.append(completion)
            self.beginInitialization()
        }
    }

    private func beginInitialization() {
        guard !initializing else { return }
        guard !channelId.isEmpty, !appKey.isEmpty, !deviceId.isEmpty else {
            finishInitialization(oaError(1000, "Configure OAS channelId/appKey and deviceId first"))
            return
        }
        initializing = true
        let attempt = revision
        let device = DeviceConfig.Builder(deviceId: deviceId)
            .setResolution(resolution).setSystemLanguage(language).build()
        let config = InitConfig.Builder(channelId: channelId, appKey: appKey, deviceConfig: device)
            .setAppUuid(appUuid).setAppChannel(appChannel).build()
        let done: (NSError?) -> Void = { error in
            DispatchQueue.main.async {
                self.initializing = false
                guard attempt == self.revision else {
                    if !self.deviceId.isEmpty { self.beginInitialization() }
                    return
                }
                if let error = error,
                   [1200, 1201, 1202, 1208, 1209, 1210].contains(error.userInfo["OASCode"] as? Int ?? error.code),
                   self.retryCount < 3 {
                    self.retryCount += 1
                    self.initializing = true
                    DispatchQueue.main.asyncAfter(deadline: .now() + Double(self.retryCount * 2)) {
                        self.initializing = false
                        if !self.deviceId.isEmpty { self.beginInitialization() }
                    }
                    return
                }
                self.ready = error == nil
                self.finishInitialization(error)
            }
        }
        OTek.initialize(config: config, onSuccess: { done(nil) },
                        onFailure: { done(oaError($0, $1)) })
    }

    private func finishInitialization(_ error: NSError?) {
        let callbacks = initializationCallbacks
        initializationCallbacks = []
        callbacks.forEach { $0(error) }
    }

    @objc public func resetDevice() {
        DispatchQueue.main.async {
            self.cancelAllOnMain()
            self.deviceId = ""
            self.ready = false
            self.revision += 1
            self.retryCount = 0
            self.finishInitialization(oaError(1204, "Device disconnected"))
        }
    }

    @objc public func cancelAll() { DispatchQueue.main.async { self.cancelAllOnMain() } }
    private func cancelAllOnMain() {
        Array(active.values).forEach { $0.finish(nil, error: oaError(1204, "OAS request cancelled")) }
    }

    /// Only the three JSON health agents belong to this channel.
    @objc(requestHealthAgentWithCode:data:language:completion:)
    public func requestHealthAgent(code: String, data: Data?, language: String?,
                                   completion: @escaping (Data?, String?, NSError?) -> Void) {
        let task = AiOASRequest(language: language?.isEmpty == false ? language! : "en-US", completion: completion)
        DispatchQueue.main.async {
            guard !task.finished else { return }
            self.active[task.id] = task
            guard ["swz-24-ErtiV9ZWQW", "swz-24-yoxRkJHouU", "swz-24-Ki3LgWLpzK", "swz-12-WZvv8s7Zzg", "swz-12-D86RHKMdfA", "swz-12-tgre5yuw4f", "yddcVTkjCCXgEM", "stztu49WdtfBnj"].contains(code) else {
                task.finish(nil, error: oaError(20026, "This OAS channel only supports the three health agents")); return
            }
            guard let data = data, !data.isEmpty,
                  let records = (try? JSONSerialization.jsonObject(with: data)) as? [[String: Any]],
                  records.count == 1, !records[0].isEmpty else {
                task.finish(nil, error: oaError(20003, "Health agent input must be a JSON array containing one object")); return
            }
            task.armDeadline()
            let start: (NSError?) -> Void = { error in
                guard !task.finished else { return }
                if let error = error { task.finish(nil, error: error); return }
                task.start(code: code, data: data)
            }
            if self.ready { start(nil) }
            else if self.initializing { self.initializationCallbacks.append(start) }
            else { start(oaError(1000, "OAS initialization has not succeeded")) }
        }
    }

}

// Keep vendor delegate types out of AiSDK-Swift.h: both SDKs export ErrorCode.
fileprivate final class AiOASRequest: NSObject, AgentDelegate {
    fileprivate let id = UUID()
    fileprivate let language: String
    fileprivate var finished = false
    private var controller: AgentController?
    private var completion: ((Data?, String?, NSError?) -> Void)?
    private var messageId = ""
    private var contextId = ""
    private var stream = AiOASStream()
    private var deadline: DispatchWorkItem?

    fileprivate init(language: String,
                     completion: @escaping (Data?, String?, NSError?) -> Void) {
        self.language = language
        self.completion = completion
    }

    fileprivate func armDeadline() {
        let item = DispatchWorkItem { [weak self] in
            self?.finish(nil, error: oaError(1207, "OAS request exceeded its time limit"))
        }
        deadline = item
        DispatchQueue.main.asyncAfter(deadline: .now() + 120, execute: item)
    }

    fileprivate func start(code: String, data: Data) {
        AiLogger.e(String(format: "[AiOAS] start id=%@ agent=%@ language=%@ inputType=textBlockBytes inputFormat=text tts=false bytes=%d", id.uuidString, code, language, data.count))
        controller = AgentController(agentConfig: AgentConfig(agentCode: code, inputLanguage: language))
        controller?.delegate = self
        run(AgentRequest.builder().setInputType(.textBlockBytes).setInputFormat(.text)
            .setTtsConfig(TTSConfig(ttsEnable: false, ttsFormat: .wav)).setData(data).build())
    }

    private func run(_ request: AgentRequest) {
        stream = AiOASStream()
        AiLogger.e(String(format: "[AiOAS] run begin id=%@", id.uuidString))
        messageId = controller?.run(request) ?? ""
        AiLogger.e(String(format: "[AiOAS] run returned id=%@ messageId=%@", id.uuidString, messageId))
        if messageId.isEmpty { finish(nil, error: oaError(1215, "OAS returned an empty message ID")) }
    }

    public func onRecognitionStopped() {} // JSON requests have no speech recognition stage.
    public func onResult(_ result: AgentResult) {
        DispatchQueue.main.async {
            AiLogger.e(String(format: "[AiOAS] result id=%@ messageId=%@ expected=%@ source=%d output=%d status=%d bytes=%d", self.id.uuidString, result.messageId, self.messageId, result.sourceType.rawValue, result.outputType.rawValue, result.status, result.data.count))
            guard !self.finished, result.messageId == self.messageId else { return }
            if [.agentReasoning, .agentThinking, .agentInternetSearch, .hint].contains(result.sourceType) { return }
            let text = [.textBlockBytes, .textStreamBytes, .textStaticStreamBytes].contains(result.outputType)
            guard text, result.sourceType == .agent else { return }
            if !result.contextId.isEmpty { self.contextId = result.contextId }
            let snapshot = result.outputType == .textStaticStreamBytes
            self.stream.receive(result.data, snapshot: snapshot, status: result.status)
            guard AiOASStream.isComplete(snapshot: snapshot, status: result.status) else { return }
            let data = self.stream.data
            guard !data.isEmpty else { self.finish(nil, error: oaError(1216, "OAS returned an empty result")); return }
            self.finish(data, error: nil)
        }
    }

    public func onError(_ error: AgentError) {
        DispatchQueue.main.async {
            AiLogger.e(String(format: "[AiOAS] error id=%@ messageId=%@ expected=%@ code=%d message=%@", self.id.uuidString, error.messageId, self.messageId, error.code, error.message))
            // Each request owns its controller; controller-level errors may have no message ID.
            guard !self.finished, error.messageId.isEmpty || error.messageId == self.messageId else { return }
            self.finish(nil, error: oaError(error.code, error.message))
        }
    }

    public func cancel() {
        if Thread.isMainThread { cancelOnMain() }
        else { DispatchQueue.main.async { self.cancelOnMain() } }
    }
    fileprivate func cancelOnMain() {
        AiLogger.e(String(format: "[AiOAS] cancel id=%@", id.uuidString))
        completion = nil
        finish(nil, error: nil)
    }
    fileprivate func finish(_ data: Data?, error: NSError?) {
        guard !finished else { return }
        finished = true
        AiLogger.e(String(format: "[AiOAS] finish id=%@ messageId=%@ contextId=%@ code=%d message=%@ bytes=%d", id.uuidString, messageId, contextId, error?.code ?? 0, error?.localizedDescription ?? "", data?.count ?? 0))
        let callback = completion
        completion = nil
        deadline?.cancel()
        controller?.delegate = nil
        controller?.destroy()
        controller = nil
        AiOASClient.shared.active.removeValue(forKey: id)
        callback?(data, contextId, error)
    }
}

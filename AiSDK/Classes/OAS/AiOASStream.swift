import Foundation

// Follow OADemo: deltas end at status 1; static STT confirms sentences at 1
// and ends the request at 2. Decode only the completed bytes, not each packet.
struct AiOASStream {
    private(set) var data = Data()
    private var confirmed = Data()
    private var partial = Data()

    mutating func receive(_ bytes: Data, snapshot: Bool, status: Int = 0) {
        if snapshot {
            if !bytes.isEmpty { partial = bytes }
            if status == 1 {
                confirmed.append(partial)
                partial = Data()
            }
            data = confirmed + partial
        } else if !bytes.isEmpty {
            data.append(bytes)
        }
    }

    static func isComplete(snapshot: Bool, status: Int) -> Bool {
        snapshot ? status == 2 : status == 1
    }
}

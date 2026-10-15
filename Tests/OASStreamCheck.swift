import Foundation

@main
struct OASStreamCheck {
    static func main() {
        var delta = AiOASStream()
        let bytes = Data("你好".utf8)
        delta.receive(bytes.prefix(2), snapshot: false)
        delta.receive(bytes.dropFirst(2), snapshot: false)
        delta.receive(Data(), snapshot: false)
        assert(String(data: delta.data, encoding: .utf8) == "你好")
        var snapshot = AiOASStream()
        snapshot.receive(Data("你".utf8), snapshot: true)
        snapshot.receive(bytes, snapshot: true)
        snapshot.receive(Data(), snapshot: true)
        assert(snapshot.data == bytes)
        snapshot.receive(Data(), snapshot: true, status: 1)
        assert(!AiOASStream.isComplete(snapshot: true, status: 1))
        snapshot.receive(Data("世界".utf8), snapshot: true, status: 0)
        snapshot.receive(Data("世界。".utf8), snapshot: true, status: 1)
        snapshot.receive(Data(), snapshot: true, status: 2)
        assert(String(data: snapshot.data, encoding: .utf8) == "你好世界。")
        assert(AiOASStream.isComplete(snapshot: true, status: 2))
        assert(AiOASStream.isComplete(snapshot: false, status: 1))
        print("OAS stream checks passed")
    }
}

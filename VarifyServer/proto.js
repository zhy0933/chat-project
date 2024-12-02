// proto.js用来解析proto文件，并将该文件中定义的消息类型和服务对象导出供其他模块使用。

const path = require('path')
const grpc = require('@grpc/grpc-js')
const protoLoader = require('@grpc/proto-loader')

const PROTO_PATH = path.join(__dirname, 'message.proto') // 定义 .proto 文件路径
const packageDefinition = protoLoader.loadSync(PROTO_PATH, { // 加载并解析 proto 文件
    keepCase: true, longs: String, enums: String,
    defaults: true, oneofs: true
})
const protoDescriptor = grpc.loadPackageDefinition(packageDefinition) // 加载 Proto 文件并创建 gRPC 服务定义
const message_proto = protoDescriptor.message // 提取服务和消息
module.exports = message_proto // 导出消息协议，使得其他文件可以引入并使用该协议
// server.js用来启动grpc server
const grpc = require('@grpc/grpc-js')
const message_proto = require('./proto')
const const_module = require('./const')
const { v4: uuidv4 } = require('uuid');
const emailModule = require('./email');
const redis_module = require('./redis')

// 响应客户端获取验证码的服务：处理客户端请求，发送验证码邮件
async function GetVarifyCode(call, callback) { // 两个参数对应.proto中的Req和Rsp
    console.log("email is ", call.request.email)
    try {
        // 防止重复生成验证码，先get查询
        let query_res = await redis_module.GetRedis(const_module.code_prefix + call.request.email);
        console.log("query_res is ", query_res)
        let uniqueId = query_res;
        // 如果还未生成
        if (query_res == null) {
            uniqueId = uuidv4();
            if (uniqueId.length > 4) {
                uniqueId = uniqueId.substring(0, 4);
            }
            let bres = await redis_module.SetRedisExpire(const_module.code_prefix + call.request.email, uniqueId, 600)
            if (!bres) {
                callback(null, {
                    email: call.request.email,
                    error: const_module.Errors.RedisErr
                });
                return;
            }
        }
        // 如果已生成
        console.log("uniqueId is ", uniqueId)
        let text_str = '您的验证码为' + uniqueId + '请三分钟内完成注册'
        let mailOptions = { // 这个对象包含了邮件的配置
            from: 'zhy554180823@163.com',
            to: call.request.email,
            subject: '验证码',
            text: text_str,
        };
        // 发送邮件。因为 SendMail 是一个promise封装的异步函数，所以这里使用 await 来等待邮件发送完成,通过promise和await把异步变成同步。
        let send_res = await emailModule.SendMail(mailOptions);
        console.log("send res is ", send_res)

        // 如果邮件发送成功，则设置 callback 回传回去
        callback(null, { 
            email: call.request.email,
            error: const_module.Errors.Success
        });

    } catch (error) { // promise返回reject时会触发异常，进入这个逻辑
        console.log("catch error is ", error)
        callback(null, {
            email: call.request.email,
            error: const_module.Errors.Exception
        });
    }
}
function main() {
    var server = new grpc.Server() // 创建一个新的 gRPC 服务器实例
    // 将 VarifyService 服务的实现（即 GetVarifyCode 函数）添加到 gRPC 服务器上
    server.addService(message_proto.VarifyService.service, { GetVarifyCode: GetVarifyCode }) // 要添加的接口，以及调用该接口的键和值，这里设置成一样的了
    // 将 gRPC 服务器绑定到 0.0.0.0: 50051 地址，并启动监听
    server.bindAsync('0.0.0.0:50051', grpc.ServerCredentials.createInsecure(), () => {
        server.start()
        console.log('grpc server started')
    })
}
main()
#include "VerifyGrpcClient.h"
#include "ConfigMgr.h"

/// <summary>
/// 调用服务端的 GetVarifyCode 方法
/// </summary>
/// <param name="email">用于获取验证码的邮箱</param>
/// <returns></returns>
GetVarifyRsp VerifyGrpcClient::GetVarifyCode(std::string email) {
    ClientContext context;
    GetVarifyRsp reply;
    GetVarifyReq request;
    request.set_email(email); // proto中定义的成员
    auto stub = pool_->getConnection(); // 从池子中获取stub
    Status status = stub->GetVarifyCode(&context, request, &reply); // 通过媒介调用服务端的方法（在proto中定义的方法）

    if (status.ok()) {
        pool_->returnConnection(std::move(stub)); // 回收stub到池子中
        return reply;
    }
    else {
        pool_->returnConnection(std::move(stub)); // 回收stub
        reply.set_error(ErrorCodes::RPCFailed); // proto中定义的成员
        return reply;
    }

}
VerifyGrpcClient::VerifyGrpcClient(){
    auto& gCfgMgr = ConfigMgr::Inst(); // 获取配置
    std::string host = gCfgMgr["VarifyServer"]["Host"];
    std::string port = gCfgMgr["VarifyServer"]["Port"];
    pool_.reset(new RPConPool(5, host, port)); // 初始化grpc连接池
}

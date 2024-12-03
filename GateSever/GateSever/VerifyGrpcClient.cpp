#include "VerifyGrpcClient.h"
#include "ConfigMgr.h"
VerifyGrpcClient::VerifyGrpcClient(){
    auto& gCfgMgr = ConfigMgr::Inst(); // 获取配置
    std::string host = gCfgMgr["VarifyServer"]["Host"];
    std::string port = gCfgMgr["VarifyServer"]["Port"];
    pool_.reset(new RPConPool(5, host, port)); // 初始化grpc连接池
}

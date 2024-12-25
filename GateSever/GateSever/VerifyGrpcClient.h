#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"
#include "RPCConPool.h"
using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;

class VerifyGrpcClient :public Singleton<VerifyGrpcClient>
{
	friend class Singleton<VerifyGrpcClient>; // 设为友元，CRTP才能调用该类构造函数
public:
	/// <summary>
	/// 调用服务端的 GetVarifyCode 方法
	/// </summary>
	/// <param name="email">用于获取验证码的邮箱</param>
	/// <returns></returns>
	GetVarifyRsp GetVarifyCode(std::string email);
private:
	// 构造函数设为私有
    VerifyGrpcClient();
    std::unique_ptr<RPConPool> pool_; // grpc连接池
};


#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"
#include "Singleton.h"
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
	GetVarifyRsp GetVarifyCode(std::string email) {
		ClientContext context;
		GetVarifyRsp reply;
		GetVarifyReq request;
		request.set_email(email); // proto中定义的成员

		Status status = stub_->GetVarifyCode(&context, request, &reply); // 通过媒介调用服务端的方法（在proto中定义的方法）

		if (status.ok()) {
			return reply;
		}
		else {
			reply.set_error(ErrorCodes::RPCFailed); // proto中定义的成员
			return reply;
		}

	}
private:
	VerifyGrpcClient() {  // 构造函数设为私有
		// stub是通过通道channel通信的，在构造函数中初始化（没有为什么）
		std::shared_ptr<Channel> channel = grpc::CreateChannel("127.0.0.1:50051", 
			grpc::InsecureChannelCredentials()); 
		stub_ = VarifyService::NewStub(channel);
	}
	std::unique_ptr<VarifyService::Stub> stub_; // 客户端与服务端的通信媒介
};


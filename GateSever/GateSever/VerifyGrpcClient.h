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

// 因为多个连接调用GetVarifyCode时会共用stub_导致线程不安全，所以将grpc连接改为连接池
class RPConPool {
public:
    RPConPool(size_t poolSize, std::string host, std::string port)
        : poolSize_(poolSize), host_(host), port_(port), b_stop_(false) {
        // stub是通过通道channel通信的（没有为什么）
        for (size_t i = 0; i < poolSize_; ++i) {
            std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, // 创建多个channel并与对应的grpc服务器连接
                grpc::InsecureChannelCredentials());
            connections_.push(VarifyService::NewStub(channel)); // 通过channel创建stub并插入队列
        }
    }
    ~RPConPool() { // 在析构中关闭所有stub即清空队列
        std::lock_guard<std::mutex> lock(mutex_);
        Close();
        while (!connections_.empty()) {
            connections_.pop();
        }
    }

    // 从池子中获取stub媒介
    std::unique_ptr<VarifyService::Stub> getConnection() {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this] { // lambda表达式返回false时挂起等待，即队列为空时
            if (b_stop_) {
                return true;
            }
            return !connections_.empty();
            });
        //如果停止则直接返回空指针
        if (b_stop_) {
            return  nullptr;
        }
        auto context = std::move(connections_.front()); // unique_ptr没有拷贝构造所以用move
        connections_.pop();
        return context;
    }

    // stub媒介用完之后要放回池子中
    void returnConnection(std::unique_ptr<VarifyService::Stub> context) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (b_stop_) {
            return;
        }
        connections_.push(std::move(context));
        cond_.notify_one(); // 还一个就只通知一个
    }
    void Close() {
        b_stop_ = true;
        cond_.notify_all(); // 通知挂起线程无需等待队列了
    }
private:
    std::atomic<bool> b_stop_; // 标记是否停止,变量是原子的
    size_t poolSize_;
    std::string host_;
    std::string port_;
    std::queue<std::unique_ptr<VarifyService::Stub>> connections_; // stub是客户端与服务端的通信媒介
    std::mutex mutex_;
    std::condition_variable cond_;
};

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
private:
	// 构造函数设为私有
    VerifyGrpcClient();
    std::unique_ptr<RPConPool> pool_; // grpc连接池
};


#pragma once
#include <grpcpp/grpcpp.h>
#include "message.grpc.pb.h"
#include "const.h"

using grpc::Channel;
using grpc::Status;
using grpc::ClientContext;

using message::GetVarifyReq;
using message::GetVarifyRsp;
using message::VarifyService;
// 因为多个连接调用GetVarifyCode时会共用stub_导致线程不安全，所以将grpc连接改为连接池
class RPConPool {
public:
    RPConPool(size_t poolSize, std::string host, std::string port);
    ~RPConPool();

    // 从池子中获取stub媒介
    std::unique_ptr<VarifyService::Stub> getConnection();

    // stub媒介用完之后要放回池子中
    void returnConnection(std::unique_ptr<VarifyService::Stub> context);
    void Close();
private:
    std::atomic<bool> b_stop_; // 标记是否停止,变量是原子的
    size_t poolSize_;
    std::string host_;
    std::string port_;
    std::queue<std::unique_ptr<VarifyService::Stub>> connections_; // stub是客户端与服务端的通信媒介
    std::mutex mutex_;
    std::condition_variable cond_;
};

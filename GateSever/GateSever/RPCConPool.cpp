#include "RPCConPool.h"
RPConPool::RPConPool(size_t poolSize, std::string host, std::string port)
    : poolSize_(poolSize), host_(host), port_(port), b_stop_(false) {
    // stub是通过通道channel通信的（没有为什么）
    for (size_t i = 0; i < poolSize_; ++i) {
        std::shared_ptr<Channel> channel = grpc::CreateChannel(host + ":" + port, // 创建多个channel并与对应的grpc服务器连接
            grpc::InsecureChannelCredentials());
        connections_.push(VarifyService::NewStub(channel)); // 通过channel创建stub并插入队列
    }
}

RPConPool::~RPConPool() { // 在析构中关闭所有stub即清空队列
    std::lock_guard<std::mutex> lock(mutex_);
    Close();
    while (!connections_.empty()) {
        connections_.pop();
    }
}

// 从池子中获取stub媒介
std::unique_ptr<VarifyService::Stub> RPConPool::getConnection() {
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
void RPConPool::returnConnection(std::unique_ptr<VarifyService::Stub> context) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (b_stop_) {
        return;
    }
    connections_.push(std::move(context));
    cond_.notify_one(); // 还一个就只通知一个
}

void RPConPool::Close() {
    b_stop_ = true;
    cond_.notify_all(); // 通知挂起线程无需等待队列了
}

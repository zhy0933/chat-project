#pragma once
#include "const.h"
class RedisConPool {
public:
    RedisConPool(size_t poolSize, const char* host, int port, const char* pwd);
    ~RedisConPool();
    // 从池中获取连接
    redisContext* getConnection();
    // 还连接回去
    void returnConnection(redisContext* context);

    void Close();
private:
    std::atomic<bool> b_stop_;
    size_t poolSize_;
    const char* host_;
    int port_;
    std::queue<redisContext*> connections_;
    std::mutex mutex_;
    std::condition_variable cond_;
};

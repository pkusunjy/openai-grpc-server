#pragma once

#include <cpp_redis/cpp_redis>

namespace plugin {

class RedisClient {
public:
    static RedisClient& instance() {
        static RedisClient instance;
        return instance;
    }
    RedisClient() = default;
    ~RedisClient() = default;
    int32_t initialize();
    void sync_commit();

private:
    cpp_redis::client _client;
};

}
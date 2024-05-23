#pragma once

#include <cpp_redis/cpp_redis>
#include "yaml-cpp/yaml.h"

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
    void commit();

private:
    cpp_redis::client _client;
    YAML::Node _config;
};

}
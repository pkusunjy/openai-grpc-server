#include "redis_client.h"
#include "log_sink.h"

namespace plugin {

int32_t RedisClient::initialize() {
    _client.connect("127.0.0.1", 6379, [](const std::string& host, std::size_t port, cpp_redis::connect_state status) {
        if (status == cpp_redis::connect_state::dropped) {
            LOG(WARNING) << "client disconnected from " << host << ":" << port;
        }
    });
    return 0;
}

void RedisClient::sync_commit() {
    _client.sync_commit();
}

}
#include "redis_client.h"
#include "log_sink.h"

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"

ABSL_FLAG(std::string, redis_conf, "./conf/redis.yaml", "redis config");

namespace plugin {

int32_t RedisClient::initialize() {
    _config = YAML::LoadFile(absl::GetFlag(FLAGS_redis_conf));
    auto host = _config["host"].as<std::string>();
    auto port = _config["port"].as<std::size_t>();
    int32_t ret {};
    _client.connect(host, port, [&](const std::string& host, std::size_t port, cpp_redis::connect_state status) {
        if (status == cpp_redis::connect_state::dropped) {
            LOG(WARNING) << "client disconnected from " << host << ":" << port;
            ret = -1;
        }
    });
    if (ret == 0) {
        // use db10
        auto db_idx = _config["db"].as<int32_t>();
        _client.select(db_idx);
        _client.sync_commit();
    }
    return ret;
}

void RedisClient::commit() {
    _client.sync_commit();
}

}
#include "redis_client.h"

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"
#include "log_sink.h"

#include <sstream>

ABSL_FLAG(std::string, redis_conf, "./conf/redis.yaml", "redis config");

namespace plugin {

int32_t RedisClient::initialize() {
  _config = YAML::LoadFile(absl::GetFlag(FLAGS_redis_conf));
  auto host = _config["host"].as<std::string>();
  auto port = _config["port"].as<std::size_t>();
  int32_t ret{};
  _client.connect(host, port, [&](const std::string& host, std::size_t port, cpp_redis::connect_state status) {
    if (status == cpp_redis::connect_state::dropped) {
      LOG(WARNING) << "client disconnected from " << host << ":" << port;
      ret = -1;
    }
    else {
      LOG(INFO) << "redis client connect " << host << ":" << port << " success";
    }
  });
  if (ret == 0) {
    // use db10
    auto db_idx = _config["db"].as<int32_t>();
    std::stringstream ss;
    _client.select(db_idx, [&](cpp_redis::reply& reply) {
      ss << reply;
    }).sync_commit();
    LOG(INFO) << "RedisClient select db res: " << ss.str();
  }
  return ret;
}

void RedisClient::sync_commit() {
  _client.sync_commit();
}

void RedisClient::set(const std::string& key, const std::string& value) {
  std::stringstream ss;
  _client.set(key, value, [&](cpp_redis::reply& reply) {
      ss << reply;
  }).sync_commit();
  LOG(INFO) << "RedisClient set key:" << key << " value:" << value << " reply:" << ss.str();
}

std::string RedisClient::get(const std::string& key) {
  std::stringstream ss;
  std::string res;
  _client.get(key, [&](cpp_redis::reply& reply) {
    ss << reply;
    if (reply.is_string()) {
      res.assign(reply.as_string());
    }
  }).sync_commit();
  LOG(INFO) << "RedisClient get key:" << key << " value:" << res << ", reply:" << ss.str();
  return res;
}

} // namespace plugin
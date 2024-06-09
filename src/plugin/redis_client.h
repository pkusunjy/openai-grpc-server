#pragma once

#include <cpp_redis/cpp_redis>

#include "yaml-cpp/yaml.h"

namespace plugin {

class RedisClient {
 public:
  int32_t initialize();
  void sync_commit();
  void set(const std::string& key, const std::string& value);
  std::string get(const std::string& key);

 private:
  cpp_redis::client _client;
  YAML::Node _config;
};

} // namespace plugin
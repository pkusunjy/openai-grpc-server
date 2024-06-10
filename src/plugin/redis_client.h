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
  void hmset(const std::string& table_name, const std::vector<std::pair<std::string, std::string>>& kv);
  std::vector<std::string> hmget(const std::string& table_name, const std::vector<std::string>& keys);
  std::vector<std::pair<std::string, std::string>> hgetall(const std::string& table_name);

 private:
  cpp_redis::client _client;
  YAML::Node _config;
};

} // namespace plugin
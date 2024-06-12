#include "redis_client.h"

#include <sstream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"
#include "log_sink.h"

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
    } else {
      LOG(INFO) << "redis client connect " << host << ":" << port << " success";
    }
  });
  if (ret == 0) {
    // use db10
    auto db_idx = _config["db"].as<int32_t>();
    std::stringstream ss;
    _client
        .select(db_idx,
                [&](cpp_redis::reply& reply) {
                  ss << reply;
                })
        .sync_commit();
    LOG(INFO) << "RedisClient select db res: " << ss.str();
  }
  return ret;
}

void RedisClient::sync_commit() {
  _client.sync_commit();
}

void RedisClient::set(const std::string& key, const std::string& value) {
  std::stringstream ss;
  ss << "key:" << key << " value:" << value;
  _client
      .set(key, value,
           [&](cpp_redis::reply& reply) {
             ss << " reply:" << reply;
           })
      .sync_commit();
  LOG(INFO) << "RedisClient set " << ss.str();
}

std::string RedisClient::get(const std::string& key) {
  std::stringstream ss;
  ss << "key:" << key;
  std::string res;
  if (!exists(key)) {
    ss << " not exist";
  } else {
    _client
        .get(key,
             [&](cpp_redis::reply& reply) {
               if (reply.is_string()) {
                 res.assign(reply.as_string());
                 ss << " value:" << res;
               }
               ss << "reply:" << reply;
             })
        .sync_commit();
  }
  LOG(INFO) << "RedisClient get " << ss.str();
  return res;
}

bool RedisClient::exists(const std::string& key) {
  std::stringstream ss;
  ss << "key:" << key;
  bool ret = false;
  _client
      .exists({key},
              [&](cpp_redis::reply& reply) {
                if (reply.is_integer() && reply.as_integer() == 1) {
                  ret = true;
                }
                ss << " reply:" << reply;
              })
      .sync_commit();
  return ret;
}

void RedisClient::hmset(const std::string& table_name, const std::vector<std::pair<std::string, std::string>>& kv) {
  std::stringstream ss;
  ss << "table_name:" << table_name << " kv:";
  for (const auto& [k, v] : kv) {
    ss << "[" << k << "," << v << "]";
  }
  _client
      .hmset(table_name, kv,
             [&](cpp_redis::reply& reply) {
               ss << " reply:" << reply;
             })
      .sync_commit();
  LOG(INFO) << "RedisClient hmset " << ss.str();
}

std::vector<std::string> RedisClient::hmget(const std::string& table_name, const std::vector<std::string>& keys) {
  std::stringstream ss;
  ss << "table_name:" << table_name << " keys:";
  for (const auto& k : keys) {
    ss << k << ",";
  }
  std::vector<std::string> values;
  values.reserve(keys.size());
  _client
      .hmget(table_name, keys,
             [&](cpp_redis::reply& reply) {
               if (reply.is_array()) {
                 const std::vector<cpp_redis::reply>& arr = reply.as_array();
                 for (const cpp_redis::reply& elem : arr) {
                   if (elem.is_null()) {
                     values.emplace_back("{}");
                   }
                   if (elem.is_string()) {
                     values.emplace_back(elem.as_string());
                   }
                 }
               }
             })
      .sync_commit();
  ss << " values:";
  for (const auto& value : values) {
    ss << value << ",";
  }
  LOG(INFO) << "RedisClient hmget " << ss.str();
  return values;
}
std::vector<std::pair<std::string, std::string>> RedisClient::hgetall(const std::string& table_name) {
  std::stringstream ss;
  ss << "table_name:" << table_name;
  std::vector<std::pair<std::string, std::string>> res;
  if (!exists(table_name)) {
    ss << " not exist";
  } else {
    _client
        .hgetall(table_name,
                 [&](cpp_redis::reply& reply) {
                   if (reply.is_array()) {
                     const std::vector<cpp_redis::reply>& arr = reply.as_array();
                     size_t idx = 0;
                     for (; idx < arr.size() - 1; idx += 2) {
                       if (arr[idx].is_string() && arr[idx + 1].is_string()) {
                         std::pair<std::string, std::string> pair =
                             std::make_pair(arr[idx].as_string(), arr[idx + 1].as_string());
                         ss << "[" << pair.first << "," << pair.second << "]";
                         res.emplace_back(pair);
                       }
                     }
                   } else {
                     ss << "reply:" << reply;
                   }
                 })
        .sync_commit();
  }
  LOG(INFO) << "RedisClient hgetall " << ss.str();
  return res;
}

void RedisClient::hdel(const std::string& table_name, const std::vector<std::string>& keys) {
  std::stringstream ss;
  ss << "table_name:" << table_name << " keys:";
  for (const auto& key : keys) {
    ss << key << ",";
  }
  _client
      .hdel(table_name, keys,
            [&](cpp_redis::reply& reply) {
              ss << " reply:" << reply;
            })
      .sync_commit();
  LOG(INFO) << "RedisClient hdel " << ss.str();
}

} // namespace plugin

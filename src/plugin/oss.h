#pragma once
#include <memory>

#include "alibabacloud/oss/OssClient.h"
#include "yaml-cpp/yaml.h"

namespace plugin {
class OssClient {
 public:
  OssClient() = default;
  ~OssClient();
  int32_t initialize();
  int32_t put_object(const std::string& bucket_name, const std::string& object_name, const std::string& local_path);
  int32_t get_object(const std::string& bucket_name, const std::string& object_name, const std::string& local_path);
  int32_t list_objects(const std::string& bucket_name, std::vector<std::string>& object_names);
  int32_t delete_object(const std::string& bucket_name, const std::string& object_name);

 private:
  YAML::Node _config;
  std::string _endpoint;
  std::string _access_key_id;
  std::string _access_key_secret;
  std::unique_ptr<AlibabaCloud::OSS::OssClient> _client;
};
} // namespace plugin
#include "oss.h"

#include <fstream>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"

ABSL_FLAG(std::string, aliyun_oss_file, "./conf/auth.yaml", "aliyun oss file");

namespace plugin {

OssClient::~OssClient() {
  AlibabaCloud::OSS::ShutdownSdk();
}

int32_t OssClient::initialize() {
  _config = YAML::LoadFile(absl::GetFlag(FLAGS_aliyun_oss_file));
  if (_config.size() == 0) {
    LOG(WARNING) << "aliyun_oss.yaml error";
    return -1;
  }
  _endpoint = _config["oss_endpoint"] ? _config["oss_endpoint"].as<std::string>() : "";
  _access_key_id = _config["oss_access_key_id"] ? _config["oss_access_key_id"].as<std::string>() : "";
  _access_key_secret = _config["oss_access_key_secret"] ? _config["oss_access_key_secret"].as<std::string>() : "";
  if (_endpoint.empty() || _access_key_id.empty() || _access_key_secret.empty()) {
    LOG(WARNING) << "aliyun_oss.yaml error";
    return -1;
  }
  _bucket_name = "mikiai";

  AlibabaCloud::OSS::InitializeSdk();
  AlibabaCloud::OSS::ClientConfiguration conf;
  _client = std::unique_ptr<AlibabaCloud::OSS::OssClient>(
      new AlibabaCloud::OSS::OssClient(_endpoint, _access_key_id, _access_key_secret, conf));
  if (_client == nullptr) {
    LOG(WARNING) << "OssClient initialize failed";
    return -1;
  }
  LOG(INFO) << "OssClient initialize success";
  return 0;
}

int32_t OssClient::put_object(const std::string& object_name, const std::string& local_path) {
  auto outcome = _client->PutObject(_bucket_name, object_name, local_path);
  if (!outcome.isSuccess()) {
    LOG(WARNING) << "OssClient PutObject fail"
                 << ",code:" << outcome.error().Code() << ",message:" << outcome.error().Message()
                 << ",requestId:" << outcome.error().RequestId() << std::endl;
    return -1;
  }
  return 0;
}

int32_t OssClient::get_object(const std::string& object_name, const std::string& local_path) {
  AlibabaCloud::OSS::GetObjectRequest request(_bucket_name, object_name);
  request.setResponseStreamFactory([=]() {
    return std::make_shared<std::fstream>(
        local_path, std::ios_base::out | std::ios_base::in | std::ios_base::trunc | std::ios_base::binary);
  });

  auto outcome = _client->GetObject(request);

  if (!outcome.isSuccess()) {
    LOG(WARNING) << "OssClient GetObjectToFile fail"
                 << ",code:" << outcome.error().Code() << ",message:" << outcome.error().Message()
                 << ",requestId:" << outcome.error().RequestId() << std::endl;
    return -1;
  }
  return 0;
}
int32_t OssClient::list_objects(std::vector<std::string>& object_names) {
  AlibabaCloud::OSS::ListObjectsRequest request(_bucket_name);
  auto outcome = _client->ListObjects(request);
  if (!outcome.isSuccess()) {
    LOG(WARNING) << "OssClient ListObjects fail"
                 << ",code:" << outcome.error().Code() << ",message:" << outcome.error().Message()
                 << ",requestId:" << outcome.error().RequestId() << std::endl;
    return -1;
  }
  object_names.clear();
  for (const auto& object : outcome.result().ObjectSummarys()) {
    object_names.push_back(object.Key());
  }
  return 0;
}

int32_t OssClient::delete_object(const std::string& object_name) {
  AlibabaCloud::OSS::DeleteObjectRequest request(_bucket_name, object_name);
  auto outcome = _client->DeleteObject(request);
  if (!outcome.isSuccess()) {
    LOG(WARNING) << "OssClient DeleteObject fail"
                 << ",code:" << outcome.error().Code() << ",message:" << outcome.error().Message()
                 << ",requestId:" << outcome.error().RequestId() << std::endl;
    return -1;
  }
  return 0;
}

int32_t OssClient::gen_presigned_url(const std::string& object_name, std::string& url) {
  auto outcome = _client->GeneratePresignedUrl(_bucket_name, object_name);
  if (!outcome.isSuccess()) {
    LOG(WARNING) << "OssClient GeneratePresignedUrl fail"
                 << ",code:" << outcome.error().Code() << ",message:" << outcome.error().Message()
                 << ",requestId:" << outcome.error().RequestId() << std::endl;
    return -1;
  }
  url.assign(outcome.result());
  return 0;
}

} // namespace plugin
#include "src/service/exercise_pool.h"

#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "absl/time/time.h"
#include "src/plugin/redis_client.h"

namespace exercise_pool {

int32_t ExercisePoolImpl::initialize() {
  // redis client
  _redis_client = std::make_unique<plugin::RedisClient>();
  if (_redis_client == nullptr) {
    LOG(WARNING) << "redis client plugin ctor failed";
    return -1;
  }
  if (_redis_client->initialize() != 0) {
    LOG(WARNING) << "redis client plugin initialize failed";
    return -1;
  }
  return 0;
}

grpc::Status ExercisePoolImpl::get(grpc::ServerContext* ctx, const ExercisePoolRequest* req,
                                   ExercisePoolResponse* resp) {
  auto scene = req->scene();
  if (scene == Scene::ILLEGAL) {
    LOG(WARNING) << "invalid scene";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "invalid scene");
  }
  LOG(INFO) << "received scene: " << scene;
  auto table_name = absl::StrFormat("%s_%d", _table_name_base, scene);
  LOG(INFO) << "table_name:" << table_name;
  auto kv_pairs = _redis_client->hgetall(table_name);
  for (const auto& [k, v] : kv_pairs) {
    auto item = resp->add_items();
    if (!::google::protobuf::util::JsonStringToMessage(v, item).ok()) {
      LOG(WARNING) << "JsonStringToMessage failed raw:" << v;
    }
  }
  return grpc::Status::OK;
}

grpc::Status ExercisePoolImpl::set(grpc::ServerContext* ctx, const ExercisePoolRequest* req,
                                   ExercisePoolResponse* resp) {
  auto scene = req->scene();
  if (scene == Scene::ILLEGAL) {
    LOG(WARNING) << "invalid scene";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "invalid scene");
  }
  LOG(INFO) << "received scene: " << scene;
  auto table_name = absl::StrFormat("%s_%d", _table_name_base, scene);
  std::vector<std::pair<std::string, std::string>> kv;
  for (const auto& item : req->items()) {
    auto key = absl::StrReplaceAll(item.title(), {{" ", "__"}});
    std::string value;
    if (::google::protobuf::util::MessageToJsonString(item, &value).ok()) {
      kv.emplace_back(std::make_pair(key, value));
    }
  }
  _redis_client->hmset(table_name, kv);
  resp->set_err_no(0);
  resp->set_err_msg("success");
  return grpc::Status::OK;
}

grpc::Status ExercisePoolImpl::del_by_title(grpc::ServerContext* ctx, const ExercisePoolRequest* req,
                                   ExercisePoolResponse* resp) {
  auto scene = req->scene();
  if (scene == Scene::ILLEGAL) {
    LOG(WARNING) << "invalid scene";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "invalid scene");
  }
  LOG(INFO) << "received scene: " << scene;
  auto table_name = absl::StrFormat("%s_%d", _table_name_base, scene);
  std::vector<std::string> keys;
  for (const auto& item : req->items()) {
    keys.emplace_back(absl::StrReplaceAll(item.title(), {{" ", "__"}}));
  }
  _redis_client->hdel(table_name, keys);
  resp->set_err_no(0);
  resp->set_err_msg("success");
  return grpc::Status::OK;
}

grpc::Status ExercisePoolImpl::del_by_content_index(grpc::ServerContext* ctx, const ExercisePoolRequest* req,
                                   ExercisePoolResponse* resp) {
  auto scene = req->scene();
  if (scene == Scene::ILLEGAL) {
    LOG(WARNING) << "invalid scene";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "invalid scene");
  }
  LOG(INFO) << "received scene: " << scene;
  auto table_name = absl::StrFormat("%s_%d", _table_name_base, scene);
  std::vector<std::string> keys;
  std::vector<std::vector<uint32_t>> content_idxs;
  for (const auto& item : req->items()) {
    keys.emplace_back(absl::StrReplaceAll(item.title(), {{" ", "__"}}));
    std::vector<uint32_t> tmp;
    for (const uint32_t idx : item.content_index()) {
      tmp.emplace_back(idx);
    }
    content_idxs.emplace_back(tmp);
  }
  // hmget
  auto values = _redis_client->hmget(table_name, keys);
  if (values.size() != content_idxs.size()) {
    LOG(WARNING) << "value size and index size mismatch, value:" << values.size() << " index:" << content_idxs.size();
    resp->set_err_no(1);
    resp->set_err_msg("param error");
    return grpc::Status::OK;
  }
  // do change
  size_t N = values.size();
  std::vector<std::pair<std::string, std::string>> kv;
  for (size_t i = 0; i < N; i++) {
    if (values[i] == "{}") {
      LOG(WARNING) << "empty json received, not expected";
      continue;
    }
    ExerciseItem old_item;
    if (!::google::protobuf::util::JsonStringToMessage(values[i], &old_item).ok()) {
      LOG(WARNING) << "JsonStringToMessage failed raw:" << values[i];
      continue;
    }
    std::set<uint32_t> target_idx(content_idxs[i].begin(), content_idxs[i].end());
    ExerciseItem new_item;
    new_item.set_title(old_item.title());
    new_item.set_author(old_item.author());
    new_item.set_create_time(old_item.create_time());
    new_item.set_title(old_item.title());
    for (size_t j = 0; j < old_item.content_size(); j++) {
      if (!target_idx.count(j)) {
        new_item.add_content(old_item.content(j));
      }
    }
    std::string new_value;
    if (!::google::protobuf::util::MessageToJsonString(new_item, &new_value).ok()) {
      LOG(WARNING) << "MessageToJsonString failed";
      continue;
    }
    kv.emplace_back(std::make_pair(keys[i], new_value));
  }
  _redis_client->hmset(table_name, kv);
  resp->set_err_no(0);
  resp->set_err_msg("success");
  return grpc::Status::OK;
}

} // namespace exercise_pool
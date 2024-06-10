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
    auto status = ::google::protobuf::util::JsonStringToMessage(v, item);
    if (status != absl::Status::ok) {
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
  // TODO: impl
  return grpc::Status::OK;
}

} // namespace exercise_pool
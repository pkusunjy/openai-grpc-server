#pragma once

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "exercise_pool/exercise_pool.grpc.pb.h"
#include "src/plugin/redis_client.h"
#include "google/protobuf/util/json_util.h"

namespace exercise_pool {

class ExercisePoolImpl final : public ExercisePoolService::Service {
 public:
  ExercisePoolImpl() = default;
  virtual ~ExercisePoolImpl() = default;
  int32_t initialize();
  grpc::Status get(grpc::ServerContext*, const ExercisePoolRequest*, ExercisePoolResponse*) override;
  grpc::Status set(grpc::ServerContext*, const ExercisePoolRequest*, ExercisePoolResponse*) override;

 private:
  std::string _table_name_base { "mikiai_exercise_pool" };
  std::unique_ptr<plugin::RedisClient> _redis_client;
};

} // namespace exercise_pool
#pragma once

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "exercise_pool/exercise_pool.grpc.pb.h"
#include "src/plugin/redis_client.h"

namespace exercise_pool {

class ExercisePoolImpl final : public ExercisePoolService::Service {
 public:
  ExercisePoolImpl() = default;
  virtual ~ExercisePoolImpl() = default;
  grpc::Status get(grpc::ServerContext*, const ExercisePoolRequest*, ExercisePoolResponse*) override;
  grpc::Status set(grpc::ServerContext*, const ExercisePoolRequest*, ExercisePoolResponse*) override;
};

} // namespace exercise_pool
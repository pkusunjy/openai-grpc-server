#pragma once

#include <fstream>
#include <sstream>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "absl/log/log.h"
#include "boost/scope_exit.hpp"
#include "wx_payment/wx_payment.grpc.pb.h"

namespace wx_payment {

class WxPaymentImpl final : public WxPaymentService::Service {
 public:
  WxPaymentImpl() = default;
  virtual ~WxPaymentImpl() = default;
  int32_t initialize();
  grpc::Status notify_url(grpc::ServerContext*, const NotifyUrlRequest*, NotifyUrlResponse*) override;

 private:
  int32_t generate_nonce_str(std::string& res);
};

} // namespace exercise_pool
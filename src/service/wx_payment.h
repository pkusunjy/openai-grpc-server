#pragma once

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "absl/log/log.h"
#include "absl/strings/str_join.h"
#include "wx_payment/wx_payment.grpc.pb.h"

namespace wx_payment {

struct AuthorizationInput {
  std::string http_method;
  std::string url;
  std::string timestamp;
  std::string nonce_str;
  std::string request_body;
  std::vector<std::string> get_vec() const {
    return std::vector<std::string>({http_method, url, timestamp, nonce_str, request_body});
  }
};

class NotifyServiceImpl final : public NotifyService::Service {
 public:
  NotifyServiceImpl() = default;
  virtual ~NotifyServiceImpl() = default;
  int32_t initialize();
  grpc::Status jsapi_notify_url(grpc::ServerContext*, const NotifyUrlRequest*, NotifyUrlResponse*) override;
};

} // namespace wx_payment
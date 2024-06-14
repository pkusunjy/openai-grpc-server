#pragma once

#include <fstream>
#include <sstream>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "absl/log/log.h"
#include "absl/strings/str_join.h"
#include "boost/scope_exit.hpp"
#include "openssl/evp.h"
#include "openssl/pem.h"
#include "openssl/sha.h"
#include "openssl/bio.h"
#include "openssl/err.h"
#include "openssl/buffer.h"
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

class WxPaymentImpl final : public WxPaymentService::Service {
 public:
  WxPaymentImpl() = default;
  virtual ~WxPaymentImpl() {
    EVP_cleanup();
    ERR_free_strings();
  }
  int32_t initialize();
  grpc::Status notify_url(grpc::ServerContext*, const NotifyUrlRequest*, NotifyUrlResponse*) override;

 public:
  int32_t generate_nonce_str(std::string& res);
  int32_t generate_http_authorization(const AuthorizationInput& input, std::string& res);
};

} // namespace exercise_pool
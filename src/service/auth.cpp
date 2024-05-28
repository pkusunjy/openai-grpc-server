#include "src/service/auth.h"

#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "absl/time/time.h"
#include "src/plugin/token.h"

namespace auth {

grpc::Status AuthImpl::get_wx_miniprogram_token(grpc::ServerContext* ctx, const AuthRequest* req, AuthResponse* resp) {
  auto& instance = plugin::TokenFactory::instance();
  resp->set_appid(instance.get_token_by_name("wx_appid"));
  resp->set_secret(instance.get_token_by_name("wx_secret"));
  return grpc::Status::OK;
}

grpc::Status AuthImpl::get_oss_token(grpc::ServerContext* ctx, const AuthRequest* req, AuthResponse* resp) {
  auto& instance = plugin::TokenFactory::instance();
  resp->set_oss_endpoint(instance.get_token_by_name("oss_endpoint"));
  resp->set_oss_access_key_id(instance.get_token_by_name("oss_access_key_id"));
  resp->set_oss_access_key_secret(instance.get_token_by_name("oss_access_key_secret"));
  return grpc::Status::OK;
}

} // namespace auth
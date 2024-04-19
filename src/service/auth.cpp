#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "absl/time/time.h"
#include "auth.h"
#include "src/plugin/token.h"

namespace auth {

grpc::Status AuthImpl::get_wx_miniprogram_token(grpc::ServerContext* ctx, const AuthRequest* req, AuthResponse* resp) {
    auto& instance = plugin::TokenFactory::instance();
    resp->set_token(instance.get_token_by_name("wx_miniprogram"));
    return grpc::Status::OK;
}

}
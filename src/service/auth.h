#pragma once

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "auth/auth.grpc.pb.h"

namespace auth {

class AuthImpl final : public AuthService::Service {
public:
    AuthImpl() = default;
    virtual ~AuthImpl() = default;
    grpc::Status get_wx_miniprogram_token(grpc::ServerContext*, const AuthRequest*, AuthResponse*) override;
};

}

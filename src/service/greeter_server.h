#pragma once

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "protos/demo.grpc.pb.h"

namespace demo {

class DemoServiceImpl final : public ::demo::DemoService::Service {
public:
    DemoServiceImpl() = default;
    virtual ~DemoServiceImpl() = default;
    grpc::Status SayHello(grpc::ServerContext* ctx,
            const demo::DemoRequest* request,
            demo::DemoResponse* response);
};
    
}


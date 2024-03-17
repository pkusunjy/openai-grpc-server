#include "absl/log/log.h"
#include "greeter_server.h"

namespace demo {

grpc::Status DemoServiceImpl::SayHello(grpc::ServerContext* ctx,
        const demo::DemoRequest* request,
        demo::DemoResponse* response) {
    LOG(INFO) << "request received";
    response->set_name("Hello " + request->name());
    return grpc::Status::OK;
}
    
}

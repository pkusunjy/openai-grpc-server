#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"

#include <glog/logging.h>
#include <grpcpp/grpcpp.h>

#include "proto/demo.grpc.pb.h"

ABSL_FLAG(std::string, target, "localhost:8000", "Server address");

int32_t main(int32_t argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::INFO, "./logs/my_log_");
    LOG(INFO) << "test google logging";

    std::string target_str = absl::GetFlag(FLAGS_target);
    std::unique_ptr<demo::DemoService::Stub> stub(
        demo::DemoService::NewStub(grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials()))
    );
    std::string user("sunjiayu");
    grpc::ClientContext context;
    demo::DemoRequest request;
    request.set_name(user);
    demo::DemoResponse response;
    grpc::Status status = stub->SayHello(&context, request, &response);
    if (status.ok()) {
        std::cout << response.name() << std::endl;
    }
    else {
        std::cout << status.error_code() << ": " << status.error_message() << std::endl;
    }
    return 0;
}

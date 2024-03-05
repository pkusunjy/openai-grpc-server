#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_format.h"

#include "protos/demo.pb.h"
#include "src/service/greeter_server.h"

ABSL_FLAG(uint16_t, port, 8000, "Server port for the service");

int32_t main(int32_t argc, char* argv[]) {
    absl::ParseCommandLine(argc, argv);
    std::cout << "cpp version: " << __cplusplus << std::endl;

    uint16_t port = absl::GetFlag(FLAGS_port);
    std::string server_addr = absl::StrFormat("0.0.0.0:%d", port);
    demo::DemoServiceImpl service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);
    
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_addr << std::endl;

    server->Wait();
    
    return 0;
}

#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"
#include "absl/strings/str_format.h"

#include "proto/chat_completion.pb.h"
#include "src/service/ielts_ai.h"

#include "liboai.h"

ABSL_FLAG(uint16_t, port, 8000, "Server port for the service");

int32_t main(int32_t argc, char* argv[]) {
    absl::ParseCommandLine(argc, argv);
    LOG(INFO) << "cpp version: " << __cplusplus << std::endl;

    if (!liboai::Authorization::Authorizer().SetKeyEnv("OPENAI_API_KEY")) {
        LOG(WARNING) << "OPENAI_API_KEY not found in env, server quit";
        return 0;
    }

    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();

    grpc::ServerBuilder builder;

    std::string server_addr = absl::StrFormat("0.0.0.0:%d", absl::GetFlag(FLAGS_port));
    builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());

    chat_completion::IeltsAI service;
    builder.RegisterService(&service);
    
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_addr << std::endl;

    server->Wait();
    
    return 0;
}

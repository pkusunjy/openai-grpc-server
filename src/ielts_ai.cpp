#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/log/log.h"
#include "absl/log/log_sink_registry.h"
#include "absl/strings/str_format.h"

#include "proto/chat_completion.pb.h"
#include "src/plugin/log_sink.h"
#include "src/service/ielts_ai.h"

#include "liboai.h"

ABSL_FLAG(uint16_t, port, 8000, "Server port for the service");
// ABSL_FLAG(std::string, log_file, "test.log", "File to write log messages to");

int32_t main(int32_t argc, char* argv[]) {
    absl::ParseCommandLine(argc, argv);

    plugin::DefaultLogSink default_sink;
    absl::AddLogSink(&default_sink);
    absl::InitializeLog();

    // LOG(INFO).ToSinkAlso(&default_sink) << "cpp version: " << __cplusplus << std::endl;
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
    if (service.initialize() != 0) {
        LOG(WARNING) << "IeltsAI initialize failed, server quit";
        return 0;
    }
    builder.RegisterService(&service);
    
    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_addr << std::endl;
    LOG(INFO) << "Server listening on " << server_addr;

    server->Wait();
    
    return 0;
}

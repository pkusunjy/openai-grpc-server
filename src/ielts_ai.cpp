#include "src/service/ielts_ai.h"

#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/log/log.h"
#include "absl/log/log_sink_registry.h"
#include "absl/strings/str_format.h"
#include "auth/auth.pb.h"
#include "chat_completion/chat_completion.pb.h"
#include "liboai.h"
#include "src/plugin/log_sink.h"
#include "src/plugin/token.h"
#include "src/service/auth.h"

ABSL_FLAG(uint16_t, port, 8123, "Server port for the service");
// ABSL_FLAG(std::string, log_file, "test.log", "File to write log messages
// to");

int32_t main(int32_t argc, char* argv[]) {
  absl::ParseCommandLine(argc, argv);

  plugin::DefaultLogSink default_sink;
  absl::AddLogSink(&default_sink);
  absl::InitializeLog();

  LOG(INFO) << "cpp version: " << __cplusplus;

  auto& token_instance = plugin::TokenFactory::instance();
  if (token_instance.initialize() != 0) {
    return 0;
  }

  std::string openai_api_key =
      token_instance.get_token_by_name("openai_api_key");
  LOG(INFO) << "openai_api_key: " << openai_api_key;

  if (!liboai::Authorization::Authorizer().SetKey(openai_api_key)) {
    LOG(WARNING) << "OPENAI_API_KEY not found, server quit";
    return 0;
  }

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  grpc::ServerBuilder builder;

  std::string server_addr =
      absl::StrFormat("0.0.0.0:%d", absl::GetFlag(FLAGS_port));
  builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());

  // auth
  auth::AuthImpl auth_service;
  builder.RegisterService(&auth_service);

  // chat
  chat_completion::IeltsAI chat_service;
  if (chat_service.initialize() != 0) {
    LOG(WARNING) << "IeltsAI initialize failed, server quit";
    return 0;
  }
  builder.RegisterService(&chat_service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  LOG(INFO) << "Server listening on " << server_addr;

  server->Wait();

  LOG(INFO) << "Server stopped on " << server_addr;
  return 0;
}

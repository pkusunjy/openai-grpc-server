#include "src/service/ielts_ai.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/initialize.h"
#include "absl/log/log.h"
#include "absl/log/log_sink_registry.h"
#include "absl/strings/str_format.h"
#include "boost/scope_exit.hpp"
#include "liboai.h"
#include "src/plugin/log_sink.h"
#include "src/plugin/token.h"
#include "src/service/auth.h"
#include "src/service/exercise_pool.h"
#include "src/service/ielts_ai.h"

ABSL_FLAG(uint16_t, port, 8123, "Server port for the service");
ABSL_FLAG(bool, offline_mode, false, "Whether enable ssl certification");
ABSL_FLAG(std::string, private_key, "/home/work/cert/privkey.key", "private key file");
ABSL_FLAG(std::string, cert_chain, "/home/work/cert/cert_chain.pem", "cert chain file");

std::string ReadFileContent(std::string_view filename) {
  std::ifstream ifs(filename.data());
  BOOST_SCOPE_EXIT(&ifs) {
    ifs.close();
  }
  BOOST_SCOPE_EXIT_END
  return std::string((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
}

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

  std::string openai_api_key = token_instance.get_token_by_name("openai_api_key");
  LOG(INFO) << "openai_api_key: " << openai_api_key;

  if (!liboai::Authorization::Authorizer().SetKey(openai_api_key)) {
    LOG(WARNING) << "OPENAI_API_KEY not found, server quit";
    return 0;
  }

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  grpc::ServerBuilder builder;
  std::string server_addr = absl::StrFormat("0.0.0.0:%d", absl::GetFlag(FLAGS_port));
  if (absl::GetFlag(FLAGS_offline_mode)) {
    builder.AddListeningPort(server_addr, grpc::InsecureServerCredentials());
  } else {
    grpc::SslServerCredentialsOptions ssl_opts;
    ssl_opts.pem_root_certs = "";
    ssl_opts.pem_key_cert_pairs.push_back(grpc::SslServerCredentialsOptions::PemKeyCertPair{
        ReadFileContent(absl::GetFlag(FLAGS_private_key)), ReadFileContent(absl::GetFlag(FLAGS_cert_chain))});
    builder.AddListeningPort(server_addr, grpc::SslServerCredentials(ssl_opts));
  }

  // auth
  auth::AuthImpl auth_service;
  builder.RegisterService(&auth_service);

  // exercise pool
  exercise_pool::ExercisePoolImpl exercise_pool_service;
  if (exercise_pool_service.initialize() != 0) {
    LOG(WARNING) << "ExercisePool initialize failed, server quit";
    return 0;
  }
  builder.RegisterService(&exercise_pool_service);

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

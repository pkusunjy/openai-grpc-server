#include <fstream>
#include <iostream>
#include <memory>
#include <string>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"
#include "boost/scope_exit.hpp"
#include "chat_completion/chat_completion.grpc.pb.h"
#include "grpcpp/grpcpp.h"

ABSL_FLAG(std::string, target, "localhost:8123", "Server address");
ABSL_FLAG(std::string, query, "", "your input");

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

  LOG(INFO) << "test absl logging";

  std::string target_str = absl::GetFlag(FLAGS_target);
  grpc::SslCredentialsOptions ssl_opts;
  ssl_opts.pem_root_certs = ReadFileContent("./cert/cert_chain.pem");
  std::unique_ptr<chat_completion::ChatService::Stub> stub(
      chat_completion::ChatService::NewStub(grpc::CreateChannel(target_str, grpc::SslCredentials(ssl_opts))));
  std::string query(absl::GetFlag(FLAGS_query));
  grpc::ClientContext context;
  chat_completion::ChatMessage request, response;
  request.set_content(query);
  auto stream(stub->write_article_by_title(&context, request));
  while (stream->Read(&response)) {
    std::cout << response.content();
  }
  return 0;
}

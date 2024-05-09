#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"
#include "chat_completion/chat_completion.grpc.pb.h"

#include <grpcpp/grpcpp.h>

#include <iostream>
#include <memory>
#include <string>

ABSL_FLAG(std::string, target, "localhost:8123", "Server address");
ABSL_FLAG(std::string, query, "", "your input");

int32_t main(int32_t argc, char* argv[]) {
  absl::ParseCommandLine(argc, argv);

  LOG(INFO) << "test absl logging";

  std::string target_str = absl::GetFlag(FLAGS_target);
  std::unique_ptr<chat_completion::ChatService::Stub> stub(
      chat_completion::ChatService::NewStub(
          grpc::CreateChannel(target_str, grpc::InsecureChannelCredentials())));
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

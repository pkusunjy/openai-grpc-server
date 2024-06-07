#include "src/service/ielts_ai.h"

namespace chat_completion {

int32_t IeltsAI::initialize() {
  // audio
  _audio = std::make_unique<liboai::Audio>();
  if (_audio == nullptr) {
    LOG(WARNING) << "ielts init failed";
    return -1;
  }
  // chat
  _chat_completion = std::make_unique<liboai::ChatCompletion>();
  if (_chat_completion == nullptr) {
    LOG(WARNING) << "ielts init failed";
    return -1;
  }
  _model = "gpt-3.5-turbo";
  _oss = std::make_unique<plugin::OssClient>();
  if (_oss == nullptr) {
    LOG(WARNING) << "ielts init failed";
    return -1;
  }
  if (_oss->initialize() != 0) {
    LOG(WARNING) << "oss client init failed";
    return -1;
  }
  return 0;
}

grpc::Status IeltsAI::ask(grpc::ServerContext* ctx, const ChatMessage* req, ChatMessage* resp) {
  if (_chat_completion == nullptr) {
    LOG(WARNING) << "openai chat completion not ready";
    return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "openai chat completion nullptr");
  }
  absl::Time step1 = absl::Now();
  liboai::Conversation convo;
  std::string system_data =
      "You are now an ielts teacher. "
      "I give you a title, you generate a writing article. "
      "This article should have at least 250 words and at most 300 words. "
      "This article should not talk anything about Chinese politics";
  if (!convo.SetSystemData(system_data)) {
    LOG(WARNING) << "set system data failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "conversion system data not set");
  }
  absl::Time step2 = absl::Now();
  if (!convo.AddUserData(req->content())) {
    LOG(WARNING) << "input data empty";
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "input empty, check your input");
  }
  absl::Time step3 = absl::Now();
  liboai::Response openai_resp = _chat_completion->create(_model, convo);
  absl::Time step4 = absl::Now();
  if (!convo.Update(openai_resp)) {
    LOG(WARNING) << "update conversion failed";
    return grpc::Status(grpc::StatusCode::INTERNAL, "internal error");
  }
  absl::Time step5 = absl::Now();
  LOG(INFO) << "dealing with " << req->content() << " SetSystemData " << absl::ToDoubleMilliseconds(step2 - step1)
            << " AddUserData " << absl::ToDoubleMilliseconds(step3 - step2) << " CreateCompletion "
            << absl::ToDoubleMilliseconds(step4 - step3) << " Update " << absl::ToDoubleMilliseconds(step5 - step4)
            << ", total cost time " << absl::ToDoubleMilliseconds(step5 - step1);
  resp->set_content(convo.GetLastResponse());
  return grpc::Status::OK;
}

grpc::Status IeltsAI::write_article_by_title(grpc::ServerContext* ctx, const ChatMessage* req,
                                             grpc::ServerWriter<ChatMessage>* stream) {
  if (_chat_completion == nullptr) {
    LOG(WARNING) << "openai chat completion not ready";
    return grpc::Status(grpc::StatusCode::UNAUTHENTICATED, "openai chat completion nullptr");
  }
  absl::Time step1 = absl::Now();
  liboai::Conversation convo;
  std::string system_data =
      "You are now an ielts teacher. "
      "I give you a title, you generate a writing article. "
      "This article should have at least 250 words and at most 300 words. "
      "This article should not talk anything about Chinese politics";
  if (!convo.SetSystemData(system_data)) {
    LOG(WARNING) << "set system data failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "conversion system data not set");
  }
  absl::Time step2 = absl::Now();
  if (!convo.AddUserData(req->content())) {
    LOG(WARNING) << "input data empty";
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "input empty, check your input");
  }

  std::regex pattern{"\"content\":\"(.*?)\""};
  std::smatch matches;
  auto stream_handler = [&](std::string data, intptr_t ptr) -> bool {
    auto reg_begin = std::sregex_iterator(data.begin(), data.end(), pattern);
    if (reg_begin == std::sregex_iterator()) {
      LOG(WARNING) << "regex match failed, raw: " << data;
    }
    for (auto i = reg_begin; i != std::sregex_iterator(); ++i) {
      ChatMessage resp{};
      resp.set_content((*i)[1]);
      stream->Write(std::move(resp));
    }
    return true;
  };

  absl::Time step3 = absl::Now();
  auto openai_resp =
      _chat_completion->create_async(_model, convo, std::nullopt, std::nullopt, std::nullopt, stream_handler);

  openai_resp.wait();

  absl::Time step4 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->uid() << " content " << req->content() << " SetSystemData "
            << absl::ToDoubleMilliseconds(step2 - step1) << " AddUserData " << absl::ToDoubleMilliseconds(step3 - step2)
            << " CreateCompletion " << absl::ToDoubleMilliseconds(step4 - step3) << ", total cost time "
            << absl::ToDoubleMilliseconds(step4 - step1);
  return grpc::Status::OK;
}

grpc::Status IeltsAI::transcribe_judge(grpc::ServerContext* ctx, const ChatMessage* req, ChatMessage* resp) {
  if (_audio == nullptr) {
    LOG(WARNING) << "transcribe_judge not ready";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "transcribe_judge not ready");
  }
  absl::Time step1 = absl::Now();
  LOG(INFO) << "received url: " << req->content();
  std::string filename = req->content();
  std::string local_filename = absl::StrReplaceAll(filename, {{"/", "_"}});
  if (_oss->get_object(filename, local_filename) != 0) {
    LOG(WARNING) << "OssClient get_object failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "oss error");
  }
  absl::Time step2 = absl::Now();
  // 2. call api
  auto res = _audio->transcribe(local_filename, "whisper-1");
  absl::Time step3 = absl::Now();
  // 3. response
  auto transcribe_res = res["text"].get<std::string>();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->uid() << " transcribe_res: " << transcribe_res;

  resp->set_content(transcribe_res);
  // 4. delete audio file on disk
  if (unlink(local_filename.c_str()) < 0) {
    char buf[256];
    strerror_r(errno, buf, 256);
    LOG(WARNING) << "logid " << req->logid() << "unlink failed file: " << local_filename << ", errno: " << errno << ", errmsg: " << buf;
  }
  // 5. TODO: delete aliyun oos
  absl::Time step4 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->uid() << " get from oss cost: "
            << absl::ToDoubleMilliseconds(step2 - step1) << " transcribe cost: " << absl::ToDoubleMilliseconds(step3 - step2)
            << " unlink cost: " << absl::ToDoubleMilliseconds(step4 - step3) << ", total cost: "
            << absl::ToDoubleMilliseconds(step4 - step1);
  return grpc::Status::OK;
}

} // namespace chat_completion
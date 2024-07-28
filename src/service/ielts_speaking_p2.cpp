#include "src/service/ielts_ai.h"

namespace chat_completion {

grpc::Status IeltsAI::ielts_speaking_p2_generate(grpc::ServerContext* ctx, const ChatMessage* req,
                                                 grpc::ServerWriter<ChatMessage>* stream) {
  if (_chat_completion == nullptr) {
    LOG(WARNING) << "ielts_speaking_p2_generate not ready";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "ielts_speaking_p2_generate not ready");
  }
  absl::Time step1 = absl::Now();

  liboai::Conversation convo;
  if (!convo.SetSystemData(_prompt_plugin->get_prompt_by_name(__FUNCTION__))) {
    LOG(WARNING) << "set system data failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "conversion system data not set");
  }
  if (!convo.AddUserData(req->content())) {
    LOG(WARNING) << "input data empty";
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "input empty, check your input");
  }

  auto openai_resp = _chat_completion->create_async(_model, convo, std::nullopt, std::nullopt, std::nullopt,
                                                    std::nullopt, stream_handler(stream));

  openai_resp.wait();

  absl::Time step2 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->userid() << " content " << req->content()
            << " total cost time " << absl::ToDoubleMilliseconds(step2 - step1);
  return grpc::Status::OK;
}

grpc::Status IeltsAI::ielts_speaking_p2_enrich(grpc::ServerContext* ctx, const ChatMessage* req,
                                               grpc::ServerWriter<ChatMessage>* stream) {
  if (_chat_completion == nullptr) {
    LOG(WARNING) << "ielts_speaking_p2_enrich not ready";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "ielts_speaking_p2_enrich not ready");
  }
  absl::Time step1 = absl::Now();

  liboai::Conversation convo;
  if (!convo.SetSystemData(_prompt_plugin->get_prompt_by_name(__FUNCTION__))) {
    LOG(WARNING) << "set system data failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "conversion system data not set");
  }
  if (!convo.AddUserData(req->content())) {
    LOG(WARNING) << "input data empty";
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "input empty, check your input");
  }

  auto openai_resp = _chat_completion->create_async(_model, convo, std::nullopt, std::nullopt, std::nullopt,
                                                    std::nullopt, stream_handler(stream));

  openai_resp.wait();

  absl::Time step2 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->userid() << " content " << req->content()
            << " total cost time " << absl::ToDoubleMilliseconds(step2 - step1);
  return grpc::Status::OK;
}

grpc::Status IeltsAI::ielts_speaking_p2_score(grpc::ServerContext* ctx, const ChatMessage* req,
                                              grpc::ServerWriter<ChatMessage>* stream) {
  if (_chat_completion == nullptr) {
    LOG(WARNING) << "ielts_speaking_p2_score not ready";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "ielts_speaking_p2_score not ready");
  }
  absl::Time step1 = absl::Now();

  liboai::Conversation convo;
  if (!convo.SetSystemData(_prompt_plugin->get_prompt_by_name(__FUNCTION__))) {
    LOG(WARNING) << "set system data failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "conversion system data not set");
  }
  if (!convo.AddUserData(req->content())) {
    LOG(WARNING) << "input data empty";
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "input empty, check your input");
  }

  auto openai_resp = _chat_completion->create_async(_model, convo, std::nullopt, std::nullopt, std::nullopt,
                                                    std::nullopt, stream_handler(stream));

  openai_resp.wait();

  absl::Time step2 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->userid() << " content " << req->content()
            << " total cost time " << absl::ToDoubleMilliseconds(step2 - step1);
  return grpc::Status::OK;
}

} // namespace chat_completion
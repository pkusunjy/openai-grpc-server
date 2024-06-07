#include "src/service/ielts_ai.h"

namespace chat_completion {

grpc::Status IeltsAI::toefl_speaking_p1_generate(grpc::ServerContext* ctx, const ChatMessage* req,
                                                 grpc::ServerWriter<ChatMessage>* stream) {
  if (_chat_completion == nullptr) {
    LOG(WARNING) << "toefl_speaking_p1_generate not ready";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "toefl_speaking_p1_generate not ready");
  }
  absl::Time step1 = absl::Now();

  liboai::Conversation convo;
  std::string system_data =
      "You are now a toefl speaking student. I am a toefl teacher. "
      "I ask you a question, which is transcribed from an audio by openai whisper. "
      "You should give a response. The response should be limited to 45s and within 1500 characters";
  if (!convo.SetSystemData(system_data)) {
    LOG(WARNING) << "set system data failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "conversion system data not set");
  }
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

  auto openai_resp =
      _chat_completion->create_async(_model, convo, std::nullopt, std::nullopt, std::nullopt, stream_handler);

  openai_resp.wait();

  absl::Time step2 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->uid() << " content " << req->content()
            << " total cost time " << absl::ToDoubleMilliseconds(step2 - step1);
  return grpc::Status::OK;
}

grpc::Status IeltsAI::toefl_speaking_p1_enrich(grpc::ServerContext* ctx, const ChatMessage* req,
                                               grpc::ServerWriter<ChatMessage>* stream) {
  if (_chat_completion == nullptr) {
    LOG(WARNING) << "toefl_speaking_p1_enrich not ready";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "toefl_speaking_p1_enrich not ready");
  }
  absl::Time step1 = absl::Now();

  liboai::Conversation convo;
  std::string system_data =
      "You are now a toefl speaking teacher. I am a toefl student. "
      "I give you an oral response, which is transcribed from an audio by openai whisper. "
      "You should give an enriched and better response with no more than 1500 characters. ";
  if (!convo.SetSystemData(system_data)) {
    LOG(WARNING) << "set system data failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "conversion system data not set");
  }
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

  auto openai_resp =
      _chat_completion->create_async(_model, convo, std::nullopt, std::nullopt, std::nullopt, stream_handler);

  openai_resp.wait();

  absl::Time step2 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->uid() << " content " << req->content()
            << " total cost time " << absl::ToDoubleMilliseconds(step2 - step1);
  return grpc::Status::OK;
}

grpc::Status IeltsAI::toefl_speaking_p1_score(grpc::ServerContext* ctx, const ChatMessage* req,
                                              grpc::ServerWriter<ChatMessage>* stream) {
  if (_chat_completion == nullptr) {
    LOG(WARNING) << "toefl_speaking_p1_score not ready";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "toefl_speaking_p1_score not ready");
  }
  absl::Time step1 = absl::Now();

  liboai::Conversation convo;
  std::string system_data =
      "You are now a toefl speaking teacher. I am a toefl student. "
      "I give you a paragraph, which is transcribed from an audio by openai whisper. "
      "You should give it a score. The total score is 30, just like a normal TOEFL exam. "
      "And you should give some analysis, from the following four aspects: "
      "Fluency and Coherence, Lexical Resource, Grammatical Range and Accuracy, and Pronunciation. "
      "The total amount of characters should be no more than 2000. ";
  if (!convo.SetSystemData(system_data)) {
    LOG(WARNING) << "set system data failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "conversion system data not set");
  }
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

  auto openai_resp =
      _chat_completion->create_async(_model, convo, std::nullopt, std::nullopt, std::nullopt, stream_handler);

  openai_resp.wait();

  absl::Time step2 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->uid() << " content " << req->content()
            << " total cost time " << absl::ToDoubleMilliseconds(step2 - step1);
  return grpc::Status::OK;
}

} // namespace chat_completion
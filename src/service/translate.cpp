#include "src/service/ielts_ai.h"

namespace chat_completion {

grpc::Status IeltsAI::cn_to_en(grpc::ServerContext* ctx, const ChatMessage* req,
                               grpc::ServerWriter<ChatMessage>* stream) {
  if (_chat_completion == nullptr) {
    LOG(WARNING) << "cn_to_en not ready";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "cn_to_en not ready");
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

  auto stream_handler = [&](std::string data, intptr_t ptr, liboai::Conversation&) -> bool {
    std::vector<std::string> raw_json_strs;
    do_split_and_trim(data, raw_json_strs);

    ChatMessage resp{};
    for (const auto& item : raw_json_strs) {
      if (item.empty()) {
        continue;
      }
      if (item == "[DONE]") {
        resp.clear_content();
        stream->WriteLast(resp, grpc::WriteOptions());
        break;
      }
      std::string content;
      if (parse_content(item, content) != 0) {
        LOG(WARNING) << "parse content failed input:" << item;
      }
      resp.set_content(content);
      stream->Write(resp);
    }
    return true;
  };

  auto openai_resp = _chat_completion->create_async(_model, convo, std::nullopt, std::nullopt, std::nullopt,
                                                    std::nullopt, stream_handler);

  openai_resp.wait();

  absl::Time step2 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->userid() << " content " << req->content()
            << " total cost time " << absl::ToDoubleMilliseconds(step2 - step1);
  return grpc::Status::OK;
}

grpc::Status IeltsAI::en_to_cn(grpc::ServerContext* ctx, const ChatMessage* req,
                               grpc::ServerWriter<ChatMessage>* stream) {
  if (_chat_completion == nullptr) {
    LOG(WARNING) << "en_to_cn not ready";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "en_to_cn not ready");
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

  auto stream_handler = [&](std::string data, intptr_t ptr, liboai::Conversation&) -> bool {
    std::vector<std::string> raw_json_strs;
    do_split_and_trim(data, raw_json_strs);

    ChatMessage resp{};
    for (const auto& item : raw_json_strs) {
      if (item.empty()) {
        continue;
      }
      if (item == "[DONE]") {
        resp.clear_content();
        stream->WriteLast(resp, grpc::WriteOptions());
        break;
      }
      std::string content;
      if (parse_content(item, content) != 0) {
        LOG(WARNING) << "parse content failed input:" << item;
      }
      resp.set_content(content);
      stream->Write(resp);
    }
    return true;
  };

  auto openai_resp = _chat_completion->create_async(_model, convo, std::nullopt, std::nullopt, std::nullopt,
                                                    std::nullopt, stream_handler);

  openai_resp.wait();

  absl::Time step2 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->userid() << " content " << req->content()
            << " total cost time " << absl::ToDoubleMilliseconds(step2 - step1);
  return grpc::Status::OK;
}

} // namespace chat_completion
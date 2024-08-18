#include "src/service/ielts_ai.h"

namespace chat_completion {

grpc::Status IeltsAI::ielts_talk_report_impl(grpc::ServerContext* ctx, const ExamAnswerList* req, TalkReport* resp) {
  if (_openai_chat_completion == nullptr) {
    LOG(WARNING) << "ielts_talk_report_impl not ready";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "ielts_talk_report_impl not ready");
  }

  // 数据预处理
  std::regex tags("<.*?>");
  nlohmann::json qa_list;
  ExamAnswerList cleaned_qa_list;
  for (size_t i = 0; i < req->answerlist_size(); i++) {
    auto new_item = cleaned_qa_list.add_answerlist();
    if (new_item == nullptr) {
      continue;
    }
    const auto& item = req->answerlist(i);
    new_item->set_contenttext(std::regex_replace(item.contenttext(), tags, ""));
    new_item->set_answer(std::regex_replace(item.answer(), tags, ""));
  }

  std::string json_input;
  google::protobuf::util::MessageToJsonString(cleaned_qa_list, &json_input);
  LOG(INFO) << "converted json input:" << json_input;

  absl::Time step1 = absl::Now();
  liboai::Conversation convo;
  if (!convo.SetSystemData(_prompt_plugin->get_prompt_by_name(__FUNCTION__))) {
    LOG(WARNING) << "set system data failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "conversion system data not set");
  }
  if (!convo.AddUserData(json_input)) {
    LOG(WARNING) << "input data empty";
    return grpc::Status(grpc::StatusCode::INVALID_ARGUMENT, "input empty, check your input");
  }
  if (!convo.AddResponseFormat(_ielts_talk_report_response_format)) {
    LOG(WARNING) << "set response_format failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "set response_format failed");
  }

  auto openai_resp = _openai_chat_completion->create("gpt-4o-2024-08-06", convo);
  LOG(INFO) << "received response:" << openai_resp;

  const auto& raw = openai_resp.raw_json;
  if (!raw.contains("choices") || !raw["choices"].is_array() || raw["choices"].empty()) {
    LOG(WARNING) << "check openai response failed, invalid choices field";
    return grpc::Status(grpc::StatusCode::UNKNOWN, "invalid openai response");
  }
  const auto& choice = raw["choices"][0];
  if (!choice.contains("message") || !choice["message"].contains("content") ||
      !choice["message"]["content"].is_string()) {
    LOG(WARNING) << "check openai response failed, invalid message or content field";
    return grpc::Status(grpc::StatusCode::UNKNOWN, "invalid openai response");
  }
  std::string resp_json_str = choice["message"]["content"].get<std::string>();
  LOG(INFO) << "openai return true content:" << resp_json_str;

  auto status = google::protobuf::util::JsonStringToMessage(resp_json_str, resp);
  if (!status.ok()) {
    LOG(WARNING) << "failed to convert JSON to protobuf: " << status.message() << " raw: " << resp_json_str;
    return grpc::Status(grpc::StatusCode::UNKNOWN, "json to proto message failed");
  }

  absl::Time step2 = absl::Now();
  LOG(INFO) << " total cost time " << absl::ToDoubleMilliseconds(step2 - step1);
  return grpc::Status::OK;
}

} // namespace chat_completion
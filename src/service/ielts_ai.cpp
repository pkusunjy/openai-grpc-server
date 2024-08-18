#include "src/service/ielts_ai.h"

namespace chat_completion {

int32_t IeltsAI::initialize() {
  auto& token_instance = plugin::TokenFactory::instance();
  // audio auth
  _openai_auth.SetKey(token_instance.get_token_by_name("openai_api_key"));
  _ali_auth.SetKey(token_instance.get_token_by_name("qwen_api_key"));
  // audio
  _audio = std::make_unique<liboai::Audio>();
  if (_audio == nullptr) {
    LOG(WARNING) << "liboai audio ctor failed";
    return -1;
  }
  _audio->SetAuth(_openai_auth);
  _audio->UpdateOpenAIRoot(token_instance.get_token_by_name("openai_url_root"));
  // chat
  _chat_completion = std::make_unique<liboai::ChatCompletion>();
  if (_chat_completion == nullptr) {
    LOG(WARNING) << "liboai completion ctor failed";
    return -1;
  }
  _chat_completion->SetAuth(_ali_auth);
  _chat_completion->UpdateOpenAIRoot(token_instance.get_token_by_name("qwen_url_root"));
  // openai chat
  _openai_chat_completion = std::make_unique<liboai::ChatCompletion>();
  if (_openai_chat_completion == nullptr) {
    LOG(WARNING) << "liboai completion ctor failed";
    return -1;
  }
  _openai_chat_completion->SetAuth(_openai_auth);
  _openai_chat_completion->UpdateOpenAIRoot(token_instance.get_token_by_name("openai_url_root"));
  // aliyun oss
  _oss = std::make_unique<plugin::OssClient>();
  if (_oss == nullptr || _oss->initialize() != 0) {
    LOG(WARNING) << "aliyun oss client init failed";
    return -1;
  }
  // prompt
  _prompt_plugin = std::make_unique<plugin::Prompt>();
  if (_prompt_plugin == nullptr || _prompt_plugin->initialize() != 0) {
    LOG(WARNING) << "prompt plugin initialize failed";
    return -1;
  }
  // response format for ielts talk report
  std::string ielts_talk_report_filename = "./conf/response_format/ielts_talk_report.json";
  std::ifstream ielts_talk_report(ielts_talk_report_filename);
  if (!ielts_talk_report.is_open()) {
    LOG(WARNING) << "open " << ielts_talk_report_filename << " failed";
    return -1;
  }
  BOOST_SCOPE_EXIT(&ielts_talk_report) {
    ielts_talk_report.close();
  }
  BOOST_SCOPE_EXIT_END
  ielts_talk_report >> _ielts_talk_report_response_format;

  return 0;
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
  BOOST_SCOPE_EXIT(&req, &local_filename) {
    // delete audio file on disk
    if (unlink(local_filename.c_str()) < 0) {
      char buf[256];
      strerror_r(errno, buf, 256);
      LOG(WARNING) << "logid " << req->logid() << "unlink failed file: " << local_filename << ", errno: " << errno
                   << ", errmsg: " << buf;
    }
  }
  BOOST_SCOPE_EXIT_END
  absl::Time step2 = absl::Now();
  // 2. call api
  auto res = _audio->transcribe(local_filename, "whisper-1");
  absl::Time step3 = absl::Now();
  // 3. response
  LOG(INFO) << "logid " << req->logid() << " transcribe input: " << local_filename
            << " result: " << nlohmann::to_string(res.raw_json);
  auto transcribe_res = res["text"].get<std::string>();

  resp->set_content(transcribe_res);
  // 4. TODO: delete aliyun oos
  absl::Time step4 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->userid()
            << " get from oss cost: " << absl::ToDoubleMilliseconds(step2 - step1)
            << " transcribe cost: " << absl::ToDoubleMilliseconds(step3 - step2)
            << " unlink cost: " << absl::ToDoubleMilliseconds(step4 - step3)
            << ", total cost: " << absl::ToDoubleMilliseconds(step4 - step1);
  return grpc::Status::OK;
}

grpc::Status IeltsAI::text_to_speech(grpc::ServerContext* ctx, const ChatMessage* req, ChatMessage* resp) {
  if (_audio == nullptr) {
    LOG(WARNING) << "text_to_speech not ready";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "text_to_speech not ready");
  }
  // 1. call api
  absl::Time step1 = absl::Now();
  LOG(INFO) << "received stage:" << req->stage() << " text: " << req->content();
  std::string voice = req->stage() == 1 ? "alloy" : "nova";
  std::string input = req->content();

  auto res = _audio->speech("tts-1", voice, input);

  std::string local_filename = absl::StrFormat("text_to_speech_%s_%llu.mp3", req->userid(), req->logid());
  {
    std::ofstream ocout(local_filename, std::ios::binary);
    ocout << res.content;
    ocout.close();
  }

  BOOST_SCOPE_EXIT(&req, &local_filename) {
    // delete audio file on disk
    if (unlink(local_filename.c_str()) < 0) {
      char buf[256];
      strerror_r(errno, buf, 256);
      LOG(WARNING) << "logid " << req->logid() << "unlink failed file: " << local_filename << ", errno: " << errno
                   << ", errmsg: " << buf;
    }
  }
  BOOST_SCOPE_EXIT_END
  // 2. upload to oss
  absl::Time step2 = absl::Now();
  if (_oss->put_object(local_filename, local_filename) != 0) {
    LOG(WARNING) << "OssClient put_object failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "oss error");
  }
  // 3. response
  absl::Time step3 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " text_to_speech input: " << input << " result: " << local_filename;
  std::string url;
  if (_oss->gen_presigned_url(local_filename, url) != 0) {
    LOG(WARNING) << "OssClient gen_presigned_url failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "oss error");
  }
  resp->set_content(url);
  // 4. TODO: delete aliyun oos
  absl::Time step4 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->userid()
            << " text_to_speech cost: " << absl::ToDoubleMilliseconds(step2 - step1)
            << " upload_oss cost: " << absl::ToDoubleMilliseconds(step3 - step2)
            << ", total cost: " << absl::ToDoubleMilliseconds(step3 - step1);
  return grpc::Status::OK;
}

void IeltsAI::do_split_and_trim(const std::string& input, std::vector<std::string>& output) {
  if (input.empty()) {
    return;
  }
  boost::split(output, input, boost::is_any_of("\n"), boost::token_compress_on);
  for (auto& item : output) {
    if (item.empty()) {
      continue;
    }
    boost::trim_if(item, boost::is_any_of(" \n\t"));
    // remove "data: " prefix
    if (item.size() > 6 && item.substr(0, 6) == "data: ") {
      item.assign(item.substr(6));
    }
  }
}

int32_t IeltsAI::parse_content(const std::string& input, std::string& output) {
  nlohmann::json j;

  try {
    j = nlohmann::json::parse(input);
  } catch (const nlohmann::json::parse_error& e) {
    LOG(WARNING) << "json parse error:" << e.what();
    return -1;
  }

  if (!j.contains("choices") || !j["choices"].is_array() || j["choices"].empty()) {
    return -1;
  }

  const auto& choice = j["choices"][0];
  if (!choice.contains("delta") || !choice["delta"].is_object()) {
    return -1;
  }

  const auto& delta = choice["delta"];
  if (!delta.contains("content") || !delta["content"].is_string()) {
    return -1;
  }

  output.assign(delta["content"].get<std::string>());
  return 0;
}

ChatStreamCallback IeltsAI::stream_handler(grpc::ServerWriter<chat_completion::ChatMessage>* stream) {
  return [=](std::string data, intptr_t ptr, liboai::Conversation&) -> bool {
    std::vector<std::string> raw_json_strs;
    do_split_and_trim(data, raw_json_strs);

    chat_completion::ChatMessage resp{};
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
}

} // namespace chat_completion
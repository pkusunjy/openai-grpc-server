#include "src/service/ielts_ai.h"

namespace chat_completion {

int32_t IeltsAI::initialize() {
  auto& token_instance = plugin::TokenFactory::instance();
  // audio auth
  _audio_auth.SetKey(token_instance.get_token_by_name("openai_api_key"));
  _chat_auth.SetKey(token_instance.get_token_by_name("qwen_api_key"));
  // audio
  _audio = std::make_unique<liboai::Audio>();
  if (_audio == nullptr) {
    LOG(WARNING) << "liboai audio ctor failed";
    return -1;
  }
  _audio->SetAuth(_audio_auth);
  _audio->UpdateOpenAIRoot(token_instance.get_token_by_name("openai_url_root"));
  // chat
  _chat_completion = std::make_unique<liboai::ChatCompletion>();
  if (_chat_completion == nullptr) {
    LOG(WARNING) << "liboai completion ctor failed";
    return -1;
  }
  _chat_completion->SetAuth(_chat_auth);
  _chat_completion->UpdateOpenAIRoot(token_instance.get_token_by_name("qwen_url_root"));
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

  resp->set_content(local_filename);
  // 4. TODO: delete aliyun oos
  absl::Time step4 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->userid()
            << " text_to_speech cost: " << absl::ToDoubleMilliseconds(step2 - step1)
            << " upload_oss cost: " << absl::ToDoubleMilliseconds(step3 - step2)
            << ", total cost: " << absl::ToDoubleMilliseconds(step3 - step1);
  return grpc::Status::OK;
}

} // namespace chat_completion
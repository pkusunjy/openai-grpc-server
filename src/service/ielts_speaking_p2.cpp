#include <regex>

#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "absl/strings/str_replace.h"
#include "absl/time/time.h"
#include "src/service/ielts_ai.h"

namespace chat_completion {

grpc::Status IeltsAI::ielts_speaking_p2_generate(grpc::ServerContext* ctx, const ChatMessage* req,
                                                 grpc::ServerWriter<ChatMessage>* stream) {
  if (_audio == nullptr || _chat_completion == nullptr) {
    LOG(WARNING) << "ielts_speaking_p2_generate not ready";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "ielts_speaking_p2_generate not ready");
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
  // 4. delete audio file on disk
  if (unlink(local_filename.c_str()) < 0) {
    char buf[256];
    strerror_r(errno, buf, 256);
    LOG(WARNING) << "logid " << req->logid() << "unlink failed file: " << local_filename << ", errno: " << errno << ", errmsg: " << buf;
  }
  // 5. TODO: delete aliyun oos
  absl::Time step4 = absl::Now();
  liboai::Conversation convo;
  std::string system_data =
      "You are now an ielts speaking teacher. I am an ielts student. "
      "I give you several questions, which are transcribed from an audio by openai whisper. "
      "You should give an appropriate answer for each question with 30-50 words. "
      "The total response should contain with no more than 2000 characters. ";
  if (!convo.SetSystemData(system_data)) {
    LOG(WARNING) << "set system data failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "conversion system data not set");
  }
  if (!convo.AddUserData(transcribe_res)) {
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

  absl::Time step5 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->uid() << " write_disk "
            << absl::ToDoubleMilliseconds(step2 - step1) << " transcribe " << absl::ToDoubleMilliseconds(step3 - step2)
            << " unlink " << absl::ToDoubleMilliseconds(step4 - step3) << ", total cost time "
            << " chat " << absl::ToDoubleMilliseconds(step5 - step4) << ", total cost time "
            << absl::ToDoubleMilliseconds(step5 - step1);
  return grpc::Status::OK;
}

grpc::Status IeltsAI::ielts_speaking_p2_enrich(grpc::ServerContext* ctx, const ChatMessage* req,
                                               grpc::ServerWriter<ChatMessage>* stream) {
  if (_audio == nullptr || _chat_completion == nullptr) {
    LOG(WARNING) << "ielts_speaking_p2_enrich not ready";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "ielts_speaking_p2_enrich not ready");
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
  // 4. delete audio file on disk
  if (unlink(local_filename.c_str()) < 0) {
    char buf[256];
    strerror_r(errno, buf, 256);
    LOG(WARNING) << "logid " << req->logid() << "unlink failed file: " << local_filename << ", errno: " << errno << ", errmsg: " << buf;
  }
  // 5. TODO: delete aliyun oos
  absl::Time step4 = absl::Now();
  liboai::Conversation convo;
  std::string system_data =
      "You are now an ielts speaking teacher. I am an ielts student. "
      "I give you my answer, you should enrich it and make it more formal. "
      "Your response should contain no more than 2000 characters. ";
  if (!convo.SetSystemData(system_data)) {
    LOG(WARNING) << "set system data failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "conversion system data not set");
  }
  if (!convo.AddUserData(transcribe_res)) {
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

  absl::Time step5 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->uid() << " write_disk "
            << absl::ToDoubleMilliseconds(step2 - step1) << " transcribe " << absl::ToDoubleMilliseconds(step3 - step2)
            << " unlink " << absl::ToDoubleMilliseconds(step4 - step3) << ", total cost time "
            << " chat " << absl::ToDoubleMilliseconds(step5 - step4) << ", total cost time "
            << absl::ToDoubleMilliseconds(step5 - step1);
  return grpc::Status::OK;
}

grpc::Status IeltsAI::ielts_speaking_p2_score(grpc::ServerContext* ctx, const ChatMessage* req,
                                              grpc::ServerWriter<ChatMessage>* stream) {
  if (_audio == nullptr || _chat_completion == nullptr) {
    LOG(WARNING) << "ielts_speaking_p2_score not ready";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "ielts_speaking_p2_score not ready");
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
  // 4. delete audio file on disk
  if (unlink(local_filename.c_str()) < 0) {
    char buf[256];
    strerror_r(errno, buf, 256);
    LOG(WARNING) << "logid " << req->logid() << "unlink failed file: " << local_filename << ", errno: " << errno << ", errmsg: " << buf;
  }
  // 5. TODO: delete aliyun oos
  absl::Time step4 = absl::Now();
  liboai::Conversation convo;
  std::string system_data =
      "You are now an ielts speaking teacher. I am an ielts student. "
      "I give you a paragraph, which is transcribed from an audio by openai whisper. "
      "You should give it a score. The total score is 9. "
      "And you should give some analysis, from the following four aspects: "
      "Fluency and Coherence, Lexical Resource, Grammatical Range and Accuracy, and Pronunciation. "
      "The total amount of characters should be no more than 2000. ";
  if (!convo.SetSystemData(system_data)) {
    LOG(WARNING) << "set system data failed";
    return grpc::Status(grpc::StatusCode::FAILED_PRECONDITION, "conversion system data not set");
  }
  if (!convo.AddUserData(transcribe_res)) {
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

  absl::Time step5 = absl::Now();
  LOG(INFO) << "logid " << req->logid() << " uid " << req->uid() << " write_disk "
            << absl::ToDoubleMilliseconds(step2 - step1) << " transcribe " << absl::ToDoubleMilliseconds(step3 - step2)
            << " unlink " << absl::ToDoubleMilliseconds(step4 - step3) << ", total cost time "
            << " chat " << absl::ToDoubleMilliseconds(step5 - step4) << ", total cost time "
            << absl::ToDoubleMilliseconds(step5 - step1);
  return grpc::Status::OK;
}

} // namespace chat_completion
#pragma once

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include <queue>
#include <regex>

#include "absl/log/log.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_replace.h"
#include "absl/strings/str_split.h"
#include "absl/time/time.h"
#include "boost/scope_exit.hpp"
#include "chat_completion/chat_completion.grpc.pb.h"
#include "components/audio.h"
#include "components/chat.h"
#include "src/plugin/oss.h"
#include "src/plugin/prompt.h"

namespace chat_completion {

class IeltsAI final : public ChatService::Service {
 public:
  IeltsAI() = default;
  virtual ~IeltsAI() = default;
  int32_t initialize();
  // 音频转文字
  grpc::Status transcribe_judge(grpc::ServerContext*, const ChatMessage*, ChatMessage*) override;
  // 雅思口语P1
  grpc::Status ielts_speaking_p1_generate(grpc::ServerContext*, const ChatMessage*,
                                          grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status ielts_speaking_p1_enrich(grpc::ServerContext*, const ChatMessage*,
                                        grpc::ServerWriter<ChatMessage>*) override;
  // 雅思口语P2
  grpc::Status ielts_speaking_p2_generate(grpc::ServerContext*, const ChatMessage*,
                                          grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status ielts_speaking_p2_enrich(grpc::ServerContext*, const ChatMessage*,
                                        grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status ielts_speaking_p2_score(grpc::ServerContext*, const ChatMessage*,
                                       grpc::ServerWriter<ChatMessage>*) override;
  // 雅思口语P3
  grpc::Status ielts_speaking_p3_generate(grpc::ServerContext*, const ChatMessage*,
                                          grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status ielts_speaking_p3_enrich(grpc::ServerContext*, const ChatMessage*,
                                        grpc::ServerWriter<ChatMessage>*) override;
  // 雅思写作T1
  grpc::Status ielts_writing_t1_enrich(grpc::ServerContext*, const ChatMessage*,
                                       grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status ielts_writing_t1_score(grpc::ServerContext*, const ChatMessage*,
                                      grpc::ServerWriter<ChatMessage>*) override;
  // 雅思写作T2
  grpc::Status ielts_writing_t2_generate(grpc::ServerContext*, const ChatMessage*,
                                         grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status ielts_writing_t2_enrich(grpc::ServerContext*, const ChatMessage*,
                                       grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status ielts_writing_t2_score(grpc::ServerContext*, const ChatMessage*,
                                      grpc::ServerWriter<ChatMessage>*) override;
  // 高分词汇挖掘
  grpc::Status ielts_speaking_words_synonyms(grpc::ServerContext*, const ChatMessage*,
                                             grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status ielts_speaking_words_usage(grpc::ServerContext*, const ChatMessage*,
                                          grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status ielts_writing_words_theme(grpc::ServerContext*, const ChatMessage*,
                                         grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status ielts_writing_words_synonyms(grpc::ServerContext*, const ChatMessage*,
                                            grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status ielts_writing_words_combination(grpc::ServerContext*, const ChatMessage*,
                                               grpc::ServerWriter<ChatMessage>*) override;
  // 托福口语
  grpc::Status toefl_speaking_p1_generate(grpc::ServerContext*, const ChatMessage*,
                                          grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status toefl_speaking_p1_enrich(grpc::ServerContext*, const ChatMessage*,
                                        grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status toefl_speaking_p1_score(grpc::ServerContext*, const ChatMessage*,
                                       grpc::ServerWriter<ChatMessage>*) override;
  // 托福综合写作
  grpc::Status toefl_writing_p1_enrich(grpc::ServerContext*, const ChatMessage*,
                                       grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status toefl_writing_p1_score(grpc::ServerContext*, const ChatMessage*,
                                      grpc::ServerWriter<ChatMessage>*) override;
  // 托福学术写作
  grpc::Status toefl_writing_p2_enrich(grpc::ServerContext*, const ChatMessage*,
                                       grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status toefl_writing_p2_score(grpc::ServerContext*, const ChatMessage*,
                                      grpc::ServerWriter<ChatMessage>*) override;
  // 职场邮件
  grpc::Status toefl_writing_p3_enrich(grpc::ServerContext*, const ChatMessage*,
                                       grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status toefl_writing_p3_generate(grpc::ServerContext*, const ChatMessage*,
                                         grpc::ServerWriter<ChatMessage>*) override;
  // 中英互译
  grpc::Status cn_to_en(grpc::ServerContext*, const ChatMessage*, grpc::ServerWriter<ChatMessage>*) override;
  grpc::Status en_to_cn(grpc::ServerContext*, const ChatMessage*, grpc::ServerWriter<ChatMessage>*) override;

  using StreamHandlerFunc = std::function<bool(std::string, intptr_t, liboai::Conversation&)>;

 private:
  void stream_handler() {}

 private:
  std::unique_ptr<liboai::Audio> _audio{nullptr};
  std::unique_ptr<liboai::ChatCompletion> _chat_completion{nullptr};
  std::string _model{"qwen-plus"};
  std::unique_ptr<plugin::OssClient> _oss{nullptr};
  std::unique_ptr<plugin::Prompt> _prompt_plugin{nullptr};
};

} // namespace chat_completion
#pragma once

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "components/audio.h"
#include "components/chat.h"
#include "proto/chat_completion.grpc.pb.h"

namespace chat_completion {

class IeltsAI final : public ChatService::Service {
public:
    IeltsAI() = default;
    virtual ~IeltsAI() = default;
    int32_t initialize();
    grpc::Status ask(grpc::ServerContext*, const ChatMessage*, ChatMessage*) override;
    grpc::Status write_article_by_title(grpc::ServerContext*, const ChatMessage*, grpc::ServerWriter<ChatMessage>*) override;
    grpc::Status transcribe_judge(grpc::ServerContext*, const ChatMessage*, ChatMessage*) override;

private:
    std::unique_ptr<liboai::Audio> _audio;
    std::unique_ptr<liboai::ChatCompletion> _chat_completion;
    std::string _model;
    std::string _system_data;
};

}
#pragma once

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "components/chat.h"
#include "proto/chat_completion.grpc.pb.h"

namespace chat_completion {

class IeltsAI final : public ChatService::Service {
public:
    IeltsAI() = default;
    virtual ~IeltsAI() = default;
    int32_t initialize();
    grpc::Status ask(grpc::ServerContext*, const ChatMessage*, ChatMessage*) override;
    grpc::Status ask_stream(grpc::ServerContext*, const ChatMessage*, grpc::ServerWriter<ChatMessage>*) override;

private:
    int32_t parse_delta_content(const std::string&, std::string&);

private:
    std::unique_ptr<liboai::ChatCompletion> _chat_completion;
    std::string _model;
    std::string _system_data;
};

}
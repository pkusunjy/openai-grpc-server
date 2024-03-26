#pragma once

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "components/chat.h"
#include "proto/chat_completion.grpc.pb.h"

namespace chat_completion {

class IeltsAI : public ChatService::Service {
public:
    IeltsAI() = default;
    virtual ~IeltsAI() = default;
    int32_t initialize();
    grpc::Status ask(grpc::ServerContext*, const ChatMessage*, ChatMessage*);

private:
    std::unique_ptr<liboai::ChatCompletion> _chat_completion;

private:
    std::string _model;
    std::string _system_data;
};

}
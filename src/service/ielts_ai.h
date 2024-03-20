#pragma once

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>

#include "components/chat.h"
#include "proto/chat_completion.grpc.pb.h"

namespace chat_completion {

class IeltsAI : public ChatService::Service {
public:
    IeltsAI() : _chat_completion(std::make_unique<liboai::ChatCompletion>()) {}
    virtual ~IeltsAI() = default;
    grpc::Status ask(grpc::ServerContext* ctx, const ChatMessage* request, ChatMessage* response);
private:
    std::unique_ptr<liboai::ChatCompletion> _chat_completion;
};

}
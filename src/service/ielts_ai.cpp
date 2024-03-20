#include "absl/log/log.h"
#include "ielts_ai.h"

namespace chat_completion {

grpc::Status IeltsAI::ask(grpc::ServerContext* ctx, const ChatMessage* request, ChatMessage* response) {
    if (_chat_completion == nullptr) {
        LOG(WARNING) << "openai chat completion not ready";
        return grpc::Status(
            grpc::StatusCode::UNAUTHENTICATED,
            "openai chat completion nullptr"
        );
    }
    liboai::Conversation convo;
    convo.AddUserData(request->content());
    liboai::Response openai_response = _chat_completion->create(
        "gpt-3.5-turbo", convo
    );
    convo.Update(openai_response);
    response->set_content(convo.GetLastResponse());
    return grpc::Status::OK;
}

}
#include "absl/log/log.h"
#include "absl/time/time.h"
#include "ielts_ai.h"

namespace chat_completion {

int32_t IeltsAI::initialize() {
    _chat_completion = std::make_unique<liboai::ChatCompletion>();
    if (_chat_completion == nullptr) {
        LOG(WARNING) << "ielts init failed";
        return -1;
    }
    _model = "gpt-3.5-turbo";
    _system_data = "You are an ielts teacher, I give you a title, you generate a writing article";
    return 0;
}

grpc::Status IeltsAI::ask(grpc::ServerContext* ctx, const ChatMessage* req, ChatMessage* resp) {
    if (_chat_completion == nullptr) {
        LOG(WARNING) << "openai chat completion not ready";
        return grpc::Status(
            grpc::StatusCode::UNAUTHENTICATED,
            "openai chat completion nullptr"
        );
    }
    absl::Time step1 = absl::Now();
    liboai::Conversation convo;
    if (!convo.SetSystemData(_system_data)) {
        LOG(WARNING) << "set system data failed";
        return grpc::Status(
            grpc::StatusCode::FAILED_PRECONDITION,
            "conversion system data not set"
        );
    }
    absl::Time step2 = absl::Now();
    if (!convo.AddUserData(req->content())) {
        LOG(WARNING) << "input data empty";
        return grpc::Status(
            grpc::StatusCode::INVALID_ARGUMENT,
            "input empty, check your input"
        );
    }
    auto stream_handler = [](std::string data, intptr_t ptr) -> bool {
        if (data == "[DONE]") {
            return true;
        }
        // TODO: json parse
        LOG(INFO) << "str: " << str << ", ptr: " << ptr;
        return true;
    };
    absl::Time step3 = absl::Now();
    liboai::Response openai_resp = _chat_completion->create(
        "gpt-3.5-turbo", convo, std::nullopt, std::nullopt, std::nullopt,
        stream_handler
    );
    absl::Time step4 = absl::Now();
    if (!convo.Update(openai_resp)) {
        LOG(WARNING) << "update conversion failed";
        return grpc::Status(
            grpc::StatusCode::INTERNAL,
            "internal error"
        );
    }
    absl::Time step5 = absl::Now();
    LOG(INFO) << "dealing with " << req->content()
              << " SetSystemData " << absl::ToDoubleMilliseconds(step2 - step1)
              << " AddUserData " << absl::ToDoubleMilliseconds(step3 - step2)
              << " CreateCompletion " << absl::ToDoubleMilliseconds(step4 - step3)
              << " Update " << absl::ToDoubleMilliseconds(step5 - step4)
              << ", total cost time " << absl::ToDoubleMilliseconds(step5 - step1);
    resp->set_content(convo.GetLastResponse());
    return grpc::Status::OK;
}

}
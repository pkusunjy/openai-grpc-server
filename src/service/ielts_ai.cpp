#include <regex>

#include "absl/log/log.h"
#include "absl/strings/str_split.h"
#include "absl/time/time.h"
#include "ielts_ai.h"

namespace chat_completion {

int32_t IeltsAI::initialize() {
    // audio
    _audio = std::make_unique<liboai::Audio>();
    if (_audio == nullptr) {
        LOG(WARNING) << "ielts init failed";
        return -1;
    }
    // chat
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
    absl::Time step3 = absl::Now();
    liboai::Response openai_resp = _chat_completion->create("gpt-3.5-turbo", convo);
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

grpc::Status IeltsAI::write_article_by_title(grpc::ServerContext* ctx, const ChatMessage* req, grpc::ServerWriter<ChatMessage>* stream) {
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

    std::regex pattern { "\"content\":\"(.*?)\"" };
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

    absl::Time step3 = absl::Now();
    auto openai_resp = _chat_completion->create_async(
        "gpt-3.5-turbo", convo, std::nullopt, std::nullopt, std::nullopt,
        stream_handler
    );

    openai_resp.wait();

    absl::Time step4 = absl::Now();
    LOG(INFO) << "dealing with " << req->content()
              << " SetSystemData " << absl::ToDoubleMilliseconds(step2 - step1)
              << " AddUserData " << absl::ToDoubleMilliseconds(step3 - step2)
              << " CreateCompletion " << absl::ToDoubleMilliseconds(step4 - step3)
              << ", total cost time " << absl::ToDoubleMilliseconds(step4 - step1);
    return grpc::Status::OK;
}

grpc::Status IeltsAI::transcribe_judge(grpc::ServerContext* ctx, const ChatMessage* req, ChatMessage* resp) {
    if (_audio == nullptr) {
        LOG(WARNING) << "openai audio not ready";
        return grpc::Status(
            grpc::StatusCode::UNAUTHENTICATED,
            "openai audio nullptr"
        );
    }
    // 1. TODO: write audio data to local file (up to 25MB, according to official documents);
    // 2. call api
    auto res = _audio->transcribe(
        "./somename.mp3",
        "whisper-1"
    );
    // 3. response
    resp->set_content(res["text"].get<std::string>());
    // 4. TODO: delete audio file on disk
    return grpc::Status::OK;
}

}
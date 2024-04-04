#include <regex>

#include "absl/log/log.h"
#include "absl/strings/str_split.h"
#include "absl/time/time.h"
#include "concurrentqueue.h"
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

grpc::Status IeltsAI::ask_stream(grpc::ServerContext* ctx, const ChatMessage* req, grpc::ServerWriter<ChatMessage>* stream) {
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

    moodycamel::ConcurrentQueue<std::string> q;
    std::regex pattern { "\"content\":\"(.*?)\"" };
    std::smatch matches;
    auto stream_handler = [&](std::string data, intptr_t ptr) -> bool {
        // LOG(INFO) << "data add recv: " << std::addressof(data);
        // LOG(INFO) << "data add recv: " << (void*)(data.c_str());
        LOG(INFO) << data;
        std::vector<std::string> split_ret = absl::StrSplit(data, "\n\n");
        LOG(INFO) << "data split size: " << split_ret.size();
        // LOG(INFO) << "data add recv: " << (void*)(data.c_str());
        for (const auto& item: split_ret) {
            std::string res;
            parse_delta_content(item, res);
            // if (std::regex_search(item, matches, pattern)) {
            //     LOG(INFO) << "matched: " << matches[1];
            //     ChatMessage resp;
            //     resp.set_content(matches[1]);
            //     stream->Write(std::move(resp));
            // }
            // else {
            //     LOG(INFO) << "not match, raw: " << data;
            // }
        }
        // nlohmann::json j = nlohmann::json::parse(data_cp);
        // ChatMessage resp;
        // resp.set_content(data);
        // stream->Write(std::move(resp));
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

int32_t IeltsAI::parse_delta_content(const std::string& data, std::string& res) {
    LOG(INFO) << "is this ok?";
    sleep(1);
    LOG(INFO) << "input: " << data.substr(6);
    nlohmann::json j = nlohmann::json::parse(data.substr(6));
    LOG(INFO) << "is this ok?";
    // if (!j.contains("choices")) {
    //     return -1;
    // }
    // LOG(INFO) << "is this ok?";
    // for (auto& choice: j["choices"].items()) {
    //     if (choice.value().contains("delta") && choice.value()["delta"].contains("content")) {
    //         res.assign(choice.value()["delta"]["content"].get<std::string>());
    //         return 0;
    //     }
    // }
    // LOG(INFO) << "is this ok?";
    return 0;
}

}
#include "absl/log/log.h"
#include "core/netimpl.h"

namespace openai::netimpl {

int32_t CurlHolder::initialize() {
    _curl = std::unique_ptr<CURL, std::function<void(CURL*)>>(
        curl_easy_init(), [](CURL* curl) {
            if (curl != nullptr) {
                curl_easy_cleanup(curl);
                curl = nullptr;
            }
        }
    );
    if (_curl == nullptr) {
        LOG(FATAL) << "curl_easy_init failed";
        return -1;
    }
    LOG(INFO) << "CurlHolder init success";
    return 0;
}

int32_t CurlHolder::url_encode(const std::string& src, std::string& dst) {
	char* output = curl_easy_escape(_curl.get(), src.c_str(), static_cast<int>(src.length()));
    if (output == nullptr) {
        LOG(WARNING) << "CurlHolder url_encode failed";
        return -1;
    }
    dst.assign(output);
    curl_free(output);
    return 0;
}

int32_t CurlHolder::url_decode(const std::string& src, std::string& dst) {
	char* output = curl_easy_unescape(_curl.get(), src.c_str(), static_cast<int>(src.length()), nullptr);
    if (output == nullptr) {
        LOG(WARNING) << "CurlHolder url_decode failed";
        return -1;
    }
    dst.assign(output);
    curl_free(output);
    return 0;
}

}

#pragma once

#include <memory>
#include <mutex>
#include <curl/curl.h>

namespace openai::netimpl {
class CurlHolder {
    CurlHolder() = default;
    virtual ~CurlHolder() {}

    CurlHolder(const CurlHolder&) = delete;
    CurlHolder(CurlHolder&&) = delete;

    CurlHolder& operator=(const CurlHolder&) = delete;
    CurlHolder& operator=(CurlHolder&&) = delete;

    int32_t initialize();
    int32_t url_encode(const std::string&, std::string&);
    int32_t url_decode(const std::string&, std::string&);

private:
    std::unique_ptr<CURL, std::function<void(CURL*)>> _curl { nullptr };
};

}

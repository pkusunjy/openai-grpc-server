#pragma once

#include <nlohmann/json.hpp>
#include "util/exception.h"

namespace openai {

class Response {
public:
    Response() = default;
    Response(const Response&);
    Response(Response&&);
    Response(std::string&& url, std::string&& content, std::string&& status_line,
        std::string&& reason, long status_code, double elapsed);

    template <typename T>
    nlohmann::json::const_reference operator[](const T& key) const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Response& resp);

private:
    std::string _url {};
    std::string _content {};
    std::string _status_line {};
    std::string _reason {};
    int32_t _status_code {};
    double _elapsed {};

private:
    nlohmann::json _json {};
};

}

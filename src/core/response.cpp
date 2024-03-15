#include "core/response.h"
#include "util/exception.h"

namespace openai {

Response::Response(const Response& rhs) :
    _url(rhs._url),
    _content(rhs._content),
    _status_line(rhs._status_line),
    _reason(rhs._reason),
    _status_code(rhs._status_code),
    _elapsed(rhs._elapsed) {}

Response::Response(Response&& rhs) :
    _url(std::move(rhs._url)),
    _content(std::move(rhs._content)),
    _status_line(std::move(rhs._status_line)),
    _reason(std::move(rhs._reason)),
    _status_code(rhs._status_code),
    _elapsed(rhs._elapsed) {}

Response::Response(std::string&& url, std::string&& content, std::string&& status_line,
        std::string&& reason, long status_code, double elapsed) :
        _url(url), _content(content), _status_line(status_line),
        _reason(reason), _status_code(status_code), _elapsed(elapsed) {
    try {
        if (!_content.empty() && _content[0] == '{') {
            _json = nlohmann::json::parse(_content);
        }
        else {
            _json = nlohmann::json();
        }
    }
    catch (nlohmann::json::parse_error& e) {
        throw util::OpenAIException(
            util::EType::E_FAILURETOPARSE,
            e.what(),
			"liboai::Response::Response(std::string&&, std::string&&, ...)"
        );
    }
}

template <typename T>
nlohmann::json::const_reference Response::operator[](const T& key) const noexcept {
    return _json[key];
}

std::ostream& operator<<(std::ostream& os, const Response& resp) {
    if (!resp._json.empty()) {
        os << resp._json.dump(4);
    }
    else {
        os << "null";
    }
    return os;
}


}

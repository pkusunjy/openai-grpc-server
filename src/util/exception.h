#pragma once

#include <iostream>
#include <exception>
#include <memory>

#include "magic_enum.hpp"

namespace openai::util {

enum class EType : uint8_t {
    E_FAILURETOPARSE,
    E_BADREQUEST,
    E_APIERROR,
    E_RATELIMIT,
    E_CONNECTIONERROR,
    E_FILEERROR,
    E_CURLERROR
};

class OpenAIException : public std::exception {
public:
    OpenAIException() = default;
    OpenAIException(const OpenAIException& rhs) noexcept :
            _error_type(rhs._error_type), _data(rhs._data), _locale(rhs._locale) {
        _fmt_str = _locale + ": " + _data + " (" + std::string(magic_enum::enum_name(_error_type)) + ")";
    }
    OpenAIException(OpenAIException&& rhs) noexcept :
            _error_type(rhs._error_type), _data(std::move(rhs._data)), _locale(std::move(rhs._locale)) {
        _fmt_str = _locale + ": " + _data + " (" + std::string(magic_enum::enum_name(_error_type)) + ")";
    }
    OpenAIException(EType error_type, std::string_view data, std::string_view locale) :
            _error_type(error_type), _data(data), _locale(locale) {
        _fmt_str = _locale + ": " + _data + " (" + std::string(magic_enum::enum_name(_error_type)) + ")";
    }
    const char* what() const noexcept override {
        return _fmt_str.c_str();
    }
private:
    EType _error_type;
    std::string _data;
    std::string _locale;
    std::string _fmt_str;
};

}

#pragma once

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "yaml-cpp/yaml.h"

namespace plugin {

class TokenFactory final {
 public:
  static TokenFactory& instance() {
    static TokenFactory instance;
    return instance;
  }
  int32_t initialize();
  std::string get_token_by_name(const std::string& name);

 private:
  YAML::Node _config;
};

}  // namespace plugin
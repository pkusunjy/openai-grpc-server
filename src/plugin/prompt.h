#pragma once

#include <string>

#include "yaml-cpp/yaml.h"

namespace plugin {
class Prompt {
 public:
  int32_t initialize();
  std::string get_prompt_by_name(const std::string&);

 private:
  YAML::Node _config;
};
} // namespace plugin
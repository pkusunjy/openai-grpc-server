#pragma once

#include <string>

#include "yaml-cpp/yaml.h"

namespace plugin {
class Prompt {
 public:
  int32_t initialize();
  int32_t get_prompt_by_name(const std::string&, std::string&);

 private:
  YAML::Node _config;
};
} // namespace plugin
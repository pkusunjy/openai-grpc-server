#include "prompt.h"

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"

ABSL_FLAG(std::string, prompt_conf, "./conf/prompt.yaml", "prompt conf file");

namespace plugin {

int32_t Prompt::initialize() {
  _config = YAML::LoadFile(absl::GetFlag(FLAGS_prompt_conf));
  if (_config.size() == 0) {
    LOG(WARNING) << "load prompt.yaml error";
    return -1;
  }
  return 0;
}

std::string Prompt::get_prompt_by_name(const std::string& name) {
  return _config[name] ? _config[name].as<std::string>() : "";
}

} // namespace plugin
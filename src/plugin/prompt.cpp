#include "prompt.h"

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"

ABSL_FLAG(std::string, prompt_conf, "./conf/prompt.yaml", "prompt conf file");

namespace plugin {

int32_t Prompt::initialize() {
  _config = YAML::LoadFile(absl::GetFlag(FLAGS_prompt_conf));
  if (_config.size() == 0) {
    LOG(WARNING) << "aliyun_oss.yaml error";
    return -1;
  }
  return 0;
}

int32_t Prompt::get_prompt_by_name(const std::string& name, std::string& prompt) {
  if (!_config[name]) {
    LOG(WARNING) << "prompt " << name << " not found";
    return -1;
  }
  prompt.assign(_config[name].as<std::string>());
  return 0;
}

} // namespace plugin
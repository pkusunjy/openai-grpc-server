#include "token.h"

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/log/log.h"

ABSL_FLAG(std::string, auth_file, "./conf/auth.yaml", "auth file");

namespace plugin {

int32_t TokenFactory::initialize() {
  _config = YAML::LoadFile(absl::GetFlag(FLAGS_auth_file));
  if (_config.size() == 0) {
    LOG(WARNING) << "no auth set";
    return -1;
  }
  return 0;
}

std::string TokenFactory::get_token_by_name(const std::string& name) {
  return _config[name] ? _config[name].as<std::string>() : "";
}

} // namespace plugin
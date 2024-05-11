#include "src/processor/unsupported_command.h"

namespace processor {

int32_t UnsupportedCommand::process() noexcept {
  *error_message.emit() =
      absl::StrFormat("command_no %u not supported", *command_no);
  return 0;
}

}  // namespace processor

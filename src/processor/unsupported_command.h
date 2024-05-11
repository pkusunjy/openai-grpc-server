#pragma once
#include "babylon/anyflow/builder.h"

using ::babylon::anyflow::GraphProcessor;

namespace processor {

class UnsupportedCommand : public GraphProcessor {
 public:
  virtual int32_t process() noexcept override;
  // clang-format off
  ANYFLOW_INTERFACE(
    ANYFLOW_DEPEND_DATA(uint32_t, command_no) 
    ANYFLOW_EMIT_DATA(std::string, error_message)
  )
  // clang-format on
};

} // namespace processor
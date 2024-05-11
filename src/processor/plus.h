#pragma once
#include "babylon/anyflow/builder.h"

using ::babylon::anyflow::GraphProcessor;

namespace processor {

class Plus : public GraphProcessor {
 public:
  virtual int32_t process() noexcept override;
  // clang-format off
  ANYFLOW_INTERFACE(
    ANYFLOW_DEPEND_DATA(int32_t, a)
    ANYFLOW_DEPEND_DATA(int32_t, b)
    ANYFLOW_EMIT_DATA(int32_t, c)
  )
  // clang-format on
};

} // namespace processor
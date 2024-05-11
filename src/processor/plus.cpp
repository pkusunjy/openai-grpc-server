#include "src/processor/plus.h"

namespace processor {

int32_t Plus::process() noexcept {
  *c.emit() = *a + *b;
  return 0;
}

} // namespace processor

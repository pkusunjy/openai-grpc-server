#pragma once

#include <fstream>
#include "absl/log/log.h"

namespace plugin {

class DefaultLogSink : public absl::LogSink {
public:
    DefaultLogSink();
    ~DefaultLogSink();
    void Send(const absl::LogEntry& entry) override;

private:
    std::ofstream _os;
};

}

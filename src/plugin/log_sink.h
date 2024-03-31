#pragma once

#include <mutex>
#include <fstream>
#include "absl/log/log.h"
#include "absl/time/time.h"

namespace plugin {

class DefaultLogSink : public absl::LogSink {
public:
    DefaultLogSink();
    ~DefaultLogSink();
    void Send(const absl::LogEntry& entry) override;

private:
    std::string _log_name;
    std::ofstream _os;
    absl::CivilHour _civil_hour;
    // TODO: use an explicit time zone instead
    const absl::TimeZone _time_zone { absl::LocalTimeZone() };
    std::mutex _mu;
};

}

#include <cstdio>
#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "absl/time/clock.h"
#include "log_sink.h"

namespace plugin {

DefaultLogSink::DefaultLogSink() :
        _log_name("./test.log"),
        _os(_log_name, std::ios::app) {
    _civil_hour = absl::ToCivilHour(absl::Now(), _time_zone);
}

DefaultLogSink::~DefaultLogSink() {
    _os.close();
}

void DefaultLogSink::Send(const absl::LogEntry& entry) {
    _os << entry.text_message_with_prefix_and_newline();
    _os.flush();
    absl::CivilHour cur = absl::ToCivilHour(entry.timestamp(), _time_zone);
    if (cur != _civil_hour) {
        std::unique_lock<std::mutex> lock_guard(_mu);
        // ...
        _os.close();
        std::string old_log = absl::StrFormat("%s.%llu%02d%02d%02d",
            _log_name,
            _civil_hour.year(),
            _civil_hour.month(),
            _civil_hour.day(),
            _civil_hour.hour());
        rename(_log_name.c_str(), old_log.c_str());
        _os.open(_log_name, std::ios::app);
        _civil_hour = cur;
    }
}

}
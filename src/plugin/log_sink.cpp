#include "log_sink.h"

#include <cstdio>

#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "absl/time/clock.h"

namespace plugin {

DefaultLogSink::DefaultLogSink()
    : _log_name("../logs/ielts_ai.log"),
      _log_name_wf("../logs/ielts_ai.log.wf"),
      _os(_log_name, std::ios::app),
      _os_wf(_log_name_wf, std::ios::app) {
  _civil_hour = absl::ToCivilHour(absl::Now(), _time_zone);
}

DefaultLogSink::~DefaultLogSink() {
  _os.close();
  _os_wf.close();
}

void DefaultLogSink::Send(const absl::LogEntry& entry) {
  absl::CivilHour cur = absl::ToCivilHour(entry.timestamp(), _time_zone);
  if (cur != _civil_hour) {
    std::unique_lock<std::mutex> lock_guard(_mu);
    // xxx.log.2024010106
    _os.close();
    std::string old_log = absl::StrFormat("%s.%llu%02d%02d%02d", _log_name, _civil_hour.year(), _civil_hour.month(),
                                          _civil_hour.day(), _civil_hour.hour());
    rename(_log_name.c_str(), old_log.c_str());
    _os.open(_log_name, std::ios::app);
    // xxx.log.wf.2024010106
    _os_wf.close();
    std::string old_log_wf = absl::StrFormat("%s.%llu%02d%02d%02d", _log_name_wf, _civil_hour.year(),
                                             _civil_hour.month(), _civil_hour.day(), _civil_hour.hour());
    rename(_log_name_wf.c_str(), old_log_wf.c_str());
    _os_wf.open(_log_name_wf, std::ios::app);
    _civil_hour = cur;
  }
  if (entry.log_severity() == absl::LogSeverity::kInfo) {
    _os << entry.text_message_with_prefix_and_newline();
    _os.flush();
  } else {
    _os_wf << entry.text_message_with_prefix_and_newline();
    _os_wf.flush();
  }
}

} // namespace plugin
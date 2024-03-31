#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "logging.h"

namespace plugin {

DefaultLogSink::DefaultLogSink() : _os("./test.log", std::ios::app) {}

DefaultLogSink::~DefaultLogSink() {
    _os.close();
}

void DefaultLogSink::Send(const absl::LogEntry& entry) {
    _os << entry.text_message_with_prefix_and_newline();
    _os.flush();
}

}
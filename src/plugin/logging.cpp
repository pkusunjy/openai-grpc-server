#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "logging.h"

namespace plugin {

DefaultLogSink::DefaultLogSink() : _os("./test.log", std::ios::app) {
    if (_os.is_open()) {
        LOG(INFO) << "DefaultLogSink os opened";
    }
    else {
        LOG(INFO) << "DefaultLogSink os not opened";
    }
    LOG(INFO) << "DefaultLogSink ctor called";
}

DefaultLogSink::~DefaultLogSink() {
    LOG(INFO) << "DefaultLogSink dtor called";
    _os.close();
}

void DefaultLogSink::Send(const absl::LogEntry& entry) {
    _os << entry.text_message_with_prefix_and_newline();
    _os.flush();
}

}
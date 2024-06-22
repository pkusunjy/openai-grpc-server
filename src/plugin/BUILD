package(
    default_visibility = ["//:__subpackages__"],
)

cc_library(
    name = "log_sink",
    srcs = ["log_sink.cpp"],
    hdrs = ["log_sink.h"],
    deps = [
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/strings",
        "@abseil-cpp//absl/time",
    ],
)

cc_library(
    name = "oss",
    srcs = ["oss.cpp"],
    hdrs = ["oss.h"],
    deps = [
        "//src/plugin:log_sink",
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
        "@abseil-cpp//absl/log",
        "@com_github_aliyun_oss_sdk//:aliyun_oss",
        "@yaml-cpp//:yaml-cpp",
    ],
)

cc_library(
    name = "prompt",
    srcs = ["prompt.cpp"],
    hdrs = ["prompt.h"],
    deps = [
        "//src/plugin:log_sink",
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
        "@abseil-cpp//absl/log",
        "@yaml-cpp//:yaml-cpp",
    ],
)

cc_library(
    name = "token",
    srcs = ["token.cpp"],
    hdrs = ["token.h"],
    deps = [
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
        "@abseil-cpp//absl/log",
        "@abseil-cpp//absl/strings",
        "@abseil-cpp//absl/time",
        "@yaml-cpp//:yaml-cpp",
    ],
)

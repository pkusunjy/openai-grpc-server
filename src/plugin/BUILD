package(
    default_visibility = ["//:__subpackages__"],
)

cc_library(
    name = "log_sink",
    srcs = ["log_sink.cpp"],
    hdrs = ["log_sink.h"],
    deps = [
        "@com_google_absl//absl/log",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/time",
    ],
)

cc_library(
    name = "token",
    srcs = ["token.cpp"],
    hdrs = ["token.h"],
    deps = [
        "@com_github_jbeder_yaml_cpp//:yaml-cpp",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/log",
        "@com_google_absl//absl/strings",
        "@com_google_absl//absl/time",
    ],
)

cc_library(
    name = "redis_client",
    srcs = ["redis_client.cpp"],
    hdrs = ["redis_client.h"],
    deps = [
        "@com_github_cpp_redis//:cpp_redis",
        "//src/plugin:log_sink",
    ],
)

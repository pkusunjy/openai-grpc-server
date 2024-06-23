package(
    default_visibility = ["//:__subpackages__"],
)

cc_binary(
    name = "ielts_ai",
    srcs = ["ielts_ai.cpp"],
    deps = [
        "//src/plugin:log_sink",
        "//src/plugin:oss",
        "//src/plugin:token",
        "//src/service:ielts_ai",
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
        "@abseil-cpp//absl/log:flags",
        "@abseil-cpp//absl/log:initialize",
        "@abseil-cpp//absl/strings:str_format",
        "@boost.scope_exit",
        "@com_github_d7ead_liboai//:oai",
    ],
)

cc_binary(
    name = "client_article",
    srcs = ["client_article.cpp"],
    deps = [
        "@boost.scope_exit",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_pkusunjy_openai_server_proto//:chat_completion_cc_grpc",
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
    ],
)

cc_binary(
    name = "client_transcribe",
    srcs = ["client_transcribe.cpp"],
    deps = [
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_pkusunjy_openai_server_proto//:chat_completion_cc_grpc",
        "@abseil-cpp//absl/flags:flag",
        "@abseil-cpp//absl/flags:parse",
    ],
)

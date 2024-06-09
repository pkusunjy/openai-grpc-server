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
        "//src/service:auth",
        "//src/service:exercise_pool",
        "//src/service:ielts_ai",
        "@boost//:scope_exit",
        "@com_github_d7ead_liboai//:oai",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
        "@com_google_absl//absl/log:flags",
        "@com_google_absl//absl/log:initialize",
        "@com_google_absl//absl/strings:str_format",
    ],
)

cc_binary(
    name = "client_article",
    srcs = ["client_article.cpp"],
    deps = [
        "@boost//:scope_exit",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_pkusunjy_openai_server_proto//:chat_completion_cc_grpc",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
    ],
)

cc_binary(
    name = "client_transcribe",
    srcs = ["client_transcribe.cpp"],
    deps = [
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_pkusunjy_openai_server_proto//:chat_completion_cc_grpc",
        "@com_google_absl//absl/flags:flag",
        "@com_google_absl//absl/flags:parse",
    ],
)

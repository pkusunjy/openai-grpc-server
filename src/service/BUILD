package(
    default_visibility = ["//:__subpackages__"],
)

cc_library(
    name = "auth",
    srcs = ["auth.cpp"],
    hdrs = ["auth.h"],
    deps = [
        "//src/plugin:token",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc++_reflection",
        "@com_github_pkusunjy_openai_server_proto//:auth_cc_grpc",
    ],
)

cc_library(
    name = "ielts_ai",
    srcs = ["ielts_ai.cpp"],
    hdrs = ["ielts_ai.h"],
    deps = [
        "//src/plugin:log_sink",
        "//src/plugin:redis_client",
        "@com_github_d7ead_liboai//:oai",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc++_reflection",
        "@com_github_pkusunjy_openai_server_proto//:chat_completion_cc_grpc",
    ],
)

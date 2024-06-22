package(
    default_visibility = ["//:__subpackages__"],
)

cc_library(
    name = "auth",
    srcs = [
        "auth.cpp",
    ],
    hdrs = [
        "auth.h",
    ],
    deps = [
        "//src/plugin:token",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc++_reflection",
        "@com_github_pkusunjy_openai_server_proto//:auth_cc_grpc",
    ],
)

cc_library(
    name = "ielts_ai",
    srcs = [
        "ielts_ai.cpp",
        "ielts_speaking_p1.cpp",
        "ielts_speaking_p2.cpp",
        "ielts_speaking_p3.cpp",
        "ielts_words.cpp",
        "ielts_writing_t1.cpp",
        "ielts_writing_t2.cpp",
        "toefl_speaking_p1.cpp",
        "toefl_writing_p1.cpp",
        "toefl_writing_p2.cpp",
        "toefl_writing_p3.cpp",
        "translate.cpp",
    ],
    hdrs = [
        "ielts_ai.h",
    ],
    deps = [
        "//src/plugin:log_sink",
        "//src/plugin:oss",
        "//src/plugin:prompt",
        "@com_github_d7ead_liboai//:oai",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc++_reflection",
        "@com_github_pkusunjy_openai_server_proto//:chat_completion_cc_grpc",
    ],
)

cc_library(
    name = "wx_payment",
    srcs = [
        "wx_payment.cpp",
    ],
    hdrs = [
        "wx_payment.h",
    ],
    linkopts = [
        "-lcrypto",
        "-lssl",
    ],
    deps = [
        "//src/plugin:log_sink",
        "@boost.scope_exit",
        "@com_github_cpp_base64//:base64",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc++_reflection",
        "@com_github_pkusunjy_openai_server_proto//:wx_payment_cc_grpc",
    ] + select({
        "@platforms//os:macos": [
            "@boringssl//:ssl",
            "@boringssl//:crypto",
        ],
        "//conditions:default": [],
    }),
)

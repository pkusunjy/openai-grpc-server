package(
    default_visibility = ["//:__subpackages__"],
)

cc_library(
    name = "ielts_ai",
    srcs = [
        "ielts_ai.cpp",
        "ielts_speaking_p1.cpp",
        "ielts_speaking_p2.cpp",
        "ielts_speaking_p3.cpp",
        "ielts_talk.cpp",
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
        "//src/plugin:token",
        "@boost.algorithm",
        "@boost.scope_exit",
        "@com_github_d7ead_liboai//:oai",
        "@com_github_grpc_grpc//:grpc++",
        "@com_github_grpc_grpc//:grpc++_reflection",
        "@com_github_pkusunjy_openai_server_proto//:chat_completion_cc_grpc",
    ],
)

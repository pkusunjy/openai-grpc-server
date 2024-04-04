package(
    default_visibility = ['//:__subpackages__'],
)

cc_library(
    name = 'ielts_ai',
    srcs = ['ielts_ai.cpp'],
    hdrs = ['ielts_ai.h'],
    deps = [
        '//proto:chat_completion_cc_grpc',
        '//src/plugin:log_sink',
        '@com_github_cameron314_concurrentqueue//:concurrentqueue',
        '@com_github_d7ead_liboai//:oai',
        '@com_github_grpc_grpc//:grpc++',
        '@com_github_grpc_grpc//:grpc++_reflection',
    ],
)

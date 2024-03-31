package(
    default_visibility = ['//:__subpackages__'],
)

cc_library(
    name = 'greeter_server',
    srcs = ['greeter_server.cpp'],
    hdrs = ['greeter_server.h'],
    deps = [
        '//proto:demo_cc_grpc',
        '//src/plugin:log_sink',
        '@com_github_grpc_grpc//:grpc++',
        '@com_github_grpc_grpc//:grpc++_reflection',
    ],
)

cc_library(
    name = 'ielts_ai',
    srcs = ['ielts_ai.cpp'],
    hdrs = ['ielts_ai.h'],
    deps = [
        '//proto:chat_completion_cc_grpc',
        '//src/plugin:log_sink',
        '@com_github_grpc_grpc//:grpc++',
        '@com_github_grpc_grpc//:grpc++_reflection',
        '@com_github_d7ead_liboai//:oai',
    ],
)

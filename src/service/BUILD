package(
    default_visibility = ['//:__subpackages__'],
)

cc_library(
    name = 'greeter_server',
    srcs = ['greeter_server.cpp'],
    hdrs = ['greeter_server.h'],
    deps = [
        '//proto:demo_cc_grpc',
        '@com_github_grpc_grpc//:grpc++',
        '@com_github_grpc_grpc//:grpc++_reflection',
    ],
)


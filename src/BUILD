package(
    default_visibility = ['//:__subpackages__'],
)

cc_binary(
    name = 'main',
    srcs = ['main.cpp'],
    deps = [
        '//src/service:greeter_server',
        '//src/core:netimpl',
        '//src/core:response',
        '@com_google_absl//absl/flags:flag',
        '@com_google_absl//absl/flags:parse',
        '@com_google_absl//absl/strings:str_format',
    ],
)

cc_binary(
    name = 'test_client',
    srcs = ['test_client.cpp'],
    deps = [
        '//proto:demo_cc_grpc',
        '@com_github_grpc_grpc//:grpc++',
        '@com_google_absl//absl/flags:flag',
        '@com_google_absl//absl/flags:parse',
    ],
)


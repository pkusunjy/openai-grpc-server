package(
    default_visibility = ['//:__subpackages__'],
)

cc_binary(
    name = 'main',
    srcs = ['main.cpp'],
    deps = [
        '//src/service:greeter_server',
        '@com_google_absl//absl/flags:flag',
        '@com_google_absl//absl/flags:parse',
        '@com_google_absl//absl/strings:str_format',
        '@com_github_google_glog//:glog',
    ],
)

cc_binary(
    name = 'test_client',
    srcs = ['test_client.cpp'],
    deps = [
        '//proto:demo_cc_grpc',
        '@com_github_google_glog//:glog',
        '@com_github_grpc_grpc//:grpc++',
        '@com_google_absl//absl/flags:flag',
        '@com_google_absl//absl/flags:parse',
    ],
)


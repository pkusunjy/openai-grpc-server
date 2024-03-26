package(
    default_visibility = ['//:__subpackages__'],
)

cc_binary(
    name = 'ielts_ai',
    srcs = ['ielts_ai.cpp'],
    deps = [
        '//src/service:greeter_server',
        '//src/service:ielts_ai',
        '@com_google_absl//absl/flags:flag',
        '@com_google_absl//absl/flags:parse',
        '@com_google_absl//absl/strings:str_format',
        '@com_github_d7ead_liboai//:oai',
    ],
)

cc_binary(
    name = 'test_client',
    srcs = ['test_client.cpp'],
    deps = [
        '//proto:chat_completion_cc_grpc',
        '@com_github_grpc_grpc//:grpc++',
        '@com_google_absl//absl/flags:flag',
        '@com_google_absl//absl/flags:parse',
    ],
)


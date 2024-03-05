package(
    default_visibility = ['//visibility:public'],
)

# proto
load('@rules_proto//proto:defs.bzl', 'proto_library')
load('@com_github_grpc_grpc//bazel:cc_grpc_library.bzl', 'cc_grpc_library')

proto_library(
    name = 'demo_proto',
    srcs = ['protos/demo.proto'],
)

cc_proto_library(
    name = 'demo_cc_proto',
    deps = [':demo_proto'],
)

cc_grpc_library(
    name = 'demo_cc_grpc',
    srcs = [':demo_proto'],
    grpc_only = True,
    deps = [':demo_cc_proto'],
)

# server
cc_library(
    name = 'greeter_server',
    # srcs = glob(['*.cpp'])
    srcs = ['src/service/greeter_server.cpp'],
    hdrs = ['src/service/greeter_server.h'],
    deps = [
        '//:demo_cc_grpc',
        '@com_github_grpc_grpc//:grpc++',
        '@com_github_grpc_grpc//:grpc++_reflection',
    ],
)
cc_binary(
    name = 'main',
    srcs = ['src/main.cpp'],
    deps = [
        '//:greeter_server',
        '@com_google_absl//absl/flags:flag',
        '@com_google_absl//absl/flags:parse',
        '@com_google_absl//absl/strings:str_format',
        '@com_github_google_glog//:glog',
    ],
)

cc_binary(
    name = 'test_client',
    srcs = ['src/test_client.cpp'],
    deps = [
        '//:demo_cc_grpc',
        '@com_github_google_glog//:glog',
        '@com_github_grpc_grpc//:grpc++',
        '@com_google_absl//absl/flags:flag',
        '@com_google_absl//absl/flags:parse',
    ],
)

# test
cc_test(
    name = 'test_demo',
    srcs = ['test/test_demo.cpp', 'test/main.cpp'],
    deps = ['@com_google_googletest//:gtest'],
)

cc_test(
    name = 'test_json',
    srcs = ['test/test_json.cpp', 'test/main.cpp'],
    deps = [
        '@com_google_googletest//:gtest',
        '@com_github_nlohmann_json//:json',
    ],
)


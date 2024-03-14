package(
    default_visibility = ['//:__subpackages__'],
)

# proto
load('@rules_proto//proto:defs.bzl', 'proto_library')
load('@com_github_grpc_grpc//bazel:cc_grpc_library.bzl', 'cc_grpc_library')

proto_library(
    name = 'demo_proto',
    srcs = ['demo.proto'],
    # strip_import_prefix = '/proto',
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


load("@gazelle//:def.bzl", "gazelle")
load("@io_bazel_rules_go//go:def.bzl", "go_binary", "go_library")

# gazelle:prefix github.com/example/project
gazelle(name = "gazelle")

go_library(
    name = "project_lib",
    srcs = ["main.go"],
    importpath = "github.com/example/project",
    visibility = ["//visibility:private"],
    deps = [
        "@com_github_grpc_ecosystem_grpc_gateway_v2//runtime",
        "@org_golang_google_grpc//:grpc",
        "@org_golang_google_grpc//credentials",
        "@org_golang_google_grpc//credentials/insecure",
        "@org_golang_google_grpc//grpclog",
    ],
)

go_binary(
    name = "gateway",
    embed = [":project_lib"],
    visibility = ["//visibility:public"],
)

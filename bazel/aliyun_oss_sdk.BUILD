package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "aliyun_oss_header",
    srcs = glob([
    ]),
    hdrs = glob([
        "sdk/include/alibabacloud/oss/*.h",
        "sdk/include/alibabacloud/oss/**/*.h",
    ]),
    includes = [
        "sdk/include",
        "sdk/include/alibabacloud/oss",
        "sdk/include/alibabacloud/oss/http",
    ],
    linkstatic = True,
    strip_include_prefix = "sdk/include",
    deps = [
    ],
)

cc_library(
    name = "aliyun_oss",
    srcs = glob([
        "sdk/src/*.cc",
        "sdk/src/**/*.cc",
        "sdk/src/**/*.cpp",
    ]),
    hdrs = glob([
        "sdk/src/*.h",
        "sdk/src/**/*.h",
    ]),
    includes = [
        "sdk/src/",
        "sdk/src/http",
        "sdk/src/model",
        "sdk/src/external",
    ],
    linkopts = [
        "-lpthread",
        "-lcurl",
    ] + select({
        "@platforms//os:linux": [
            "-lcrypto",
            "-lssl",
        ],
        "//conditions:default": [],
    }),
    linkstatic = True,
    strip_include_prefix = "sdk/src",
    deps = [
        ":aliyun_oss_header",
    ] + select({
        "@platforms//os:macos": [
            "@boringssl//:ssl",
            "@boringssl//:crypto",
        ],
        "//conditions:default": [],
    }),
)
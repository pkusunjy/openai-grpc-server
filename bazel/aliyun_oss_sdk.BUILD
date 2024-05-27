package(
    default_visibility = ["//visibility:public"],
)

# config_setting(
#     name = "msvc-cl",
#     flag_values = {"@bazel_tools//tools/cpp:compiler": "msvc-cl"},
# )
# 
# config_setting(
#     name = "clang-cl",
#     flag_values = {"@bazel_tools//tools/cpp:compiler": "clang-cl"},
# )
# 
# config_setting(
#     name = "opt",
#     values = {"compilation_mode": "opt"},
# )

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
        "-lcrypto",
        "-lssl",
    ],
    linkstatic = True,
    strip_include_prefix = "sdk/src",
    deps = [
        ":aliyun_oss_header",
    ],
)
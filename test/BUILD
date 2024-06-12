package(
    default_visibility = ["//:__subpackages__"],
)

# cc_test(
#     name = "test_graph",
#     srcs = [
#         "test_graph.cpp",
#     ],
#     deps = [
#         "//src/processor:graph_processor",
#         "@googletest//:gtest_main",
#     ],
# )

cc_test(
    name = "test_liboai",
    srcs = [
        "test_liboai.cpp",
    ],
    deps = [
        "@com_github_d7ead_liboai//:oai",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test_oss",
    srcs = [
        "test_oss.cpp",
    ],
    deps = [
        "//src/plugin:oss",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test_prompt",
    srcs = [
        "test_prompt.cpp",
    ],
    deps = [
        "//src/plugin:prompt",
        "@googletest//:gtest_main",
    ],
)

cc_test(
    name = "test_util",
    srcs = [
        "test_util.cpp",
    ],
    deps = [
        "@googletest//:gtest_main",
        "@nlohmann_json//:json",
    ],
)

cc_test(
    name = "test_yaml_parser",
    srcs = [
        "test_yaml_parser.cpp",
    ],
    deps = [
        "@googletest//:gtest_main",
        "@yaml-cpp//:yaml-cpp",
    ],
)

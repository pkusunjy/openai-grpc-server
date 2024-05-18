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
#         "@com_google_googletest//:gtest_main",
#     ],
# )

cc_test(
    name = "test_liboai",
    srcs = [
        "test_liboai.cpp",
    ],
    deps = [
        "@com_github_d7ead_liboai//:oai",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "test_util",
    srcs = [
        "test_util.cpp",
    ],
    deps = [
        "@com_github_nlohmann_json//:nlohmann_json",
        "@com_google_googletest//:gtest_main",
    ],
)

cc_test(
    name = "test_yaml_parser",
    srcs = [
        "test_yaml_parser.cpp",
    ],
    deps = [
        "@com_github_jbeder_yaml_cpp//:yaml-cpp",
        "@com_google_googletest//:gtest_main",
    ],
)

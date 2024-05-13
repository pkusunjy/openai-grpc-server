# cc_test(
#     name = "test_graph",
#     srcs = [
#         "main.cpp",
#         "test_graph.cpp",
#     ],
#     deps = [
#         "//src/processor",
#         "@com_google_googletest//:gtest",
#     ],
# )

cc_test(
    name = "test_liboai",
    srcs = [
        "main.cpp",
        "test_liboai.cpp",
    ],
    deps = [
        "@com_github_d7ead_liboai//:oai",
        "@com_google_googletest//:gtest",
    ],
)

cc_test(
    name = "test_util",
    srcs = [
        "main.cpp",
        "test_util.cpp",
    ],
    deps = [
        "@com_github_nlohmann_json//:nlohmann_json",
        "@com_google_googletest//:gtest",
    ],
)

cc_test(
    name = "test_yaml_parser",
    srcs = [
        "main.cpp",
        "test_yaml_parser.cpp",
    ],
    deps = [
        "@com_github_jbeder_yaml_cpp//:yaml-cpp",
        "@com_google_googletest//:gtest",
    ],
)

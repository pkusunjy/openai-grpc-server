cc_test(
    name = 'test_demo',
    srcs = ['test_demo.cpp', 'main.cpp'],
    deps = ['@com_google_googletest//:gtest'],
)

cc_test(
    name = 'test_util',
    srcs = ['test_util.cpp', 'main.cpp'],
    deps = [
        '@com_google_googletest//:gtest',
        '@com_github_nlohmann_json//:nlohmann_json',
        '//src/util:exception',
    ],
)


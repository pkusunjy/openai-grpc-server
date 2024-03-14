cc_test(
    name = 'test_demo',
    srcs = ['test_demo.cpp', 'main.cpp'],
    deps = ['@com_google_googletest//:gtest'],
)

cc_test(
    name = 'test_json',
    srcs = ['test_json.cpp', 'main.cpp'],
    deps = [
        '@com_google_googletest//:gtest',
        '@com_github_nlohmann_json//:json',
        '//src/util:exception',
    ],
)


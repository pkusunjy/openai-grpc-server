package(
    default_visibility = ['//visibility:public'],
)

cc_binary(
    name = 'main',
    srcs = ['src/main.cpp'],
    deps = ['@com_apache_brpc//:brpc']
)

cc_test(
    name = 'test_default',
    srcs = ['test/test_basic_op.cpp', 'test/main.cpp'],
    deps = ['@com_google_googletest//:gtest'],
)

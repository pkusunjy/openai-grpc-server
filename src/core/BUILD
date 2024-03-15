package(
    default_visibility = ['//:__subpackages__'],
)

cc_library(
    name = 'netimpl',
    srcs = ['netimpl.cpp'],
    hdrs = ['netimpl.h'],
    strip_include_prefix = '//src',
    deps = [
        '@com_github_curl_curl//:curl',
        '@com_google_absl//absl/log:log',
    ],
)

cc_library(
    name = 'response',
    srcs = ['response.cpp'],
    hdrs = ['response.h'],
    strip_include_prefix = '//src',
    deps = [
        '//src/util:exception',
        '@com_github_nlohmann_json//:nlohmann_json',
    ],
)

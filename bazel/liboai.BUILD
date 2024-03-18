package(
    default_visibility = ['//visibility:public'],
)

licenses(["notice"])

cc_library(
    name= 'oai',
    srcs = [
        'components/audio.cpp',
        'components/azure.cpp',
        'components/chat.cpp',
        'components/completions.cpp',
        'components/edits.cpp',
        'components/embeddings.cpp',
        'components/files.cpp',
        'components/fine_tunes.cpp',
        'components/images.cpp',
        'components/models.cpp',
        'components/moderations.cpp',
        'core/authorization.cpp',
        'core/netimpl.cpp',
        'core/response.cpp',
    ],
    hdrs = [
        'include/components/audio.h',
        'include/components/azure.h',
        'include/components/chat.h',
        'include/components/completions.h',
        'include/components/edits.h',
        'include/components/embeddings.h',
        'include/components/files.h',
        'include/components/fine_tunes.h',
        'include/components/images.h',
        'include/components/models.h',
        'include/components/moderations.h',
        'include/core/authorization.h',
        'include/core/exception.h',
        'include/core/netimpl.h',
        'include/core/network.h',
        'include/core/response.h',
        'include/liboai.h',
    ],
    strip_include_prefix = '//include',
    deps = [
        '@com_github_curl_curl//:curl',
        '@com_github_nlohmann_json//:nlohmann_json',
    ],
)

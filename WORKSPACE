workspace(name = 'ielts_ai')

load('@bazel_tools//tools/build_defs/repo:http.bzl', 'http_archive')

http_archive(
    name = 'com_google_googletest',
    urls = ['https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz'],
    strip_prefix = 'googletest-1.14.0',
    sha256 = '8ad598c73ad796e0d8280b082cebd82a630d73e73cd3c70057938a6501bba5d7',
)

http_archive(
    name = 'com_github_gflags_gflags',
    urls = ['https://github.com/gflags/gflags/archive/v2.2.2.tar.gz'],
    strip_prefix = 'gflags-2.2.2',
    sha256 = '34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf',
)

http_archive(
    name = 'com_github_google_glog',
    urls = ['https://github.com/google/glog/archive/v0.7.0.zip'],
    strip_prefix = 'glog-0.7.0',
    sha256 = '6e1216d7bc5bb785b9c596ac59b975423c0882488f46c45760d0c2a9ef77295b',
)

http_archive(
    name = 'com_github_grpc_grpc',
    urls = ['https://github.com/grpc/grpc/archive/refs/tags/v1.62.0.tar.gz'],
    strip_prefix = 'grpc-1.62.0',
    sha256 = 'f40bde4ce2f31760f65dc49a2f50876f59077026494e67dccf23992548b1b04f',
)
load('@com_github_grpc_grpc//bazel:grpc_deps.bzl', 'grpc_deps')
grpc_deps()
load('@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl', 'grpc_extra_deps')
grpc_extra_deps()

http_archive(
    name = 'com_github_nlohmann_json',
    urls = ['https://github.com/nlohmann/json/archive/v3.11.3.tar.gz'],
    strip_prefix = 'json-3.11.3',
    sha256 = '0d8ef5af7f9794e3263480193c491549b2ba6cc74bb018906202ada498a79406',
)

http_archive(
    name = 'com_github_d7ead_liboai',
    urls = ['https://github.com/D7EAD/liboai/archive/refs/tags/v3.2.1.tar.gz'],
    strip_prefix = 'liboai-3.2.1',
    build_file = '//bazel/third_party/liboai:liboai.BUILD',
    sha256 = '9058bcc1485967061c9c33b2e7a109a254cdf71638b1448f21cfefd7ffd9c4fa',
)

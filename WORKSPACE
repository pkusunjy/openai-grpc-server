workspace(name = 'openai-grpc-server')

load('@bazel_tools//tools/build_defs/repo:http.bzl', 'http_archive')

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
    name = 'com_github_googleapis_google_cloud_cpp',
    urls = ['https://github.com/googleapis/google-cloud-cpp/archive/refs/tags/v2.22.0.tar.gz'],
    strip_prefix = 'google-cloud-cpp-2.22.0',
    sha256 = '0c68782e57959c82e0c81def805c01460a042c1aae0c2feee905acaa2a2dc9bf',
)
load('@com_github_googleapis_google_cloud_cpp//bazel:google_cloud_cpp_deps.bzl', 'google_cloud_cpp_deps')
google_cloud_cpp_deps()

http_archive(
    name = 'com_github_neargye_magic_enum',
    urls = ['https://github.com/Neargye/magic_enum/archive/v0.9.5.tar.gz'],
    strip_prefix = 'magic_enum-0.9.5',
    sha256 = '44ad80db5a72f5047e01d90e18315751d9ac90c0ab42cbea7a6f9ec66a4cd679',
)

http_archive(
    name = 'com_github_d7ead_liboai',
    urls = ['https://github.com/D7EAD/liboai/archive/v3.2.1.tar.gz'],
    strip_prefix = 'liboai-3.2.1/liboai',
    build_file = '//bazel:liboai.BUILD',
    sha256 = '9058bcc1485967061c9c33b2e7a109a254cdf71638b1448f21cfefd7ffd9c4fa',
)
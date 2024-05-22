workspace(name = "openai-grpc-server")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_github_grpc_grpc",
    sha256 = "f40bde4ce2f31760f65dc49a2f50876f59077026494e67dccf23992548b1b04f",
    strip_prefix = "grpc-1.62.0",
    urls = ["https://github.com/grpc/grpc/archive/refs/tags/v1.62.0.tar.gz"],
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()

http_archive(
    name = "com_github_googleapis_google_cloud_cpp",
    sha256 = "0c68782e57959c82e0c81def805c01460a042c1aae0c2feee905acaa2a2dc9bf",
    strip_prefix = "google-cloud-cpp-2.22.0",
    urls = ["https://github.com/googleapis/google-cloud-cpp/archive/refs/tags/v2.22.0.tar.gz"],
)

load("@com_github_googleapis_google_cloud_cpp//bazel:google_cloud_cpp_deps.bzl", "google_cloud_cpp_deps")

google_cloud_cpp_deps()

http_archive(
    name = "com_github_neargye_magic_enum",
    sha256 = "44ad80db5a72f5047e01d90e18315751d9ac90c0ab42cbea7a6f9ec66a4cd679",
    strip_prefix = "magic_enum-0.9.5",
    urls = ["https://github.com/Neargye/magic_enum/archive/v0.9.5.tar.gz"],
)

http_archive(
    name = "com_github_d7ead_liboai",
    build_file = "//bazel:liboai.BUILD",
    sha256 = "8b4797ef5bc5876cba760695563bb7d0341f432abd38488620d642509c698773",
    strip_prefix = "liboai-1.0.1/liboai",
    urls = ["https://github.com/pkusunjy/liboai/archive/v1.0.1.tar.gz"],
)

http_archive(
    name = "com_github_jbeder_yaml_cpp",
    sha256 = "fbe74bbdcee21d656715688706da3c8becfd946d92cd44705cc6098bb23b3a16",
    strip_prefix = "yaml-cpp-0.8.0",
    urls = ["https://github.com/jbeder/yaml-cpp/archive/0.8.0.tar.gz"],
)

http_archive(
    name = "com_github_pkusunjy_openai_server_proto",
    sha256 = "6d247cf4d0188660180e12164c7313d8adfed0a21de20e71aa8d4e95b36a4771",
    strip_prefix = "openai-server-proto-1.0.5",
    urls = ["https://github.com/pkusunjy/openai-server-proto/archive/v1.0.5.tar.gz"],
)

http_archive(
    name = "com_github_nelhage_rules_boost",
    sha256 = "2215e6910eb763a971b1f63f53c45c0f2b7607df38c96287666d94d954da8cdc",
    strip_prefix = "rules_boost-4ab574f9a84b42b1809978114a4664184716f4bf",
    urls = ["https://github.com/nelhage/rules_boost/archive/4ab574f9a84b42b1809978114a4664184716f4bf.tar.gz"],
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")

boost_deps()

http_archive(
    name = "tacopie",
    sha256 = "bbdebecdb68d5f9eb64170217000daf844e0aee18b8c4d3dd373d07efd9f7316",
    strip_prefix = "tacopie-master",
    url = "https://github.com/cylix/tacopie/archive/master.zip",
)

http_archive(
    name = "com_github_cpp_redis",
    sha256 = "a759911f535266c2ecde1e426bc8d4f17c26cef09e8a3d94ae973160de988d8b",
    strip_prefix = "cpp_redis-master",
    urls = ["https://github.com/cpp-redis/cpp_redis/archive/refs/heads/master.zip"],
)

# http_archive(
#     name = "com_github_baidu_babylon",
#     sha256 = "626c30f7df34dee8b735d8cabd8779ceb1a9274fd73285ec850f522ad36aa7eb",
#     strip_prefix = "babylon-1.1.3",
#     urls = ["https://github.com/baidu/babylon/archive/v1.1.3.tar.gz"],
# )

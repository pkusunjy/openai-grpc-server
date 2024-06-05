workspace(name = "openai-grpc-server")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

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
    name = "com_github_pkusunjy_openai_server_proto",
    sha256 = "3de192da63a6ff90f8a9e5e8d98ab8c7001f18b018889b835b181cd94c1ee735",
    strip_prefix = "openai-server-proto-1.0.9",
    urls = ["https://github.com/pkusunjy/openai-server-proto/archive/v1.0.9.tar.gz"],
)

http_archive(
    name = "com_github_nelhage_rules_boost",
    sha256 = "627421636376b303657ada4295ad2b138f4c7cad651fb6b586569a81b0058001",
    strip_prefix = "rules_boost-a8d1aa55e7c3c2ba69b39fa521671bb32d4b98ad",
    urls = ["https://github.com/nelhage/rules_boost/archive/a8d1aa55e7c3c2ba69b39fa521671bb32d4b98ad.tar.gz"],
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

http_archive(
   name = "rules_foreign_cc",
   sha256 = "c905d5ba97d102153b7b8cacc8fa1f1c29623a710264c992cd2cddcb9d616527",
   strip_prefix = "rules_foreign_cc-0.10.1",
   url = "https://github.com/bazelbuild/rules_foreign_cc/archive/0.10.1.zip",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

rules_foreign_cc_dependencies()

http_archive(
    name = "openssl",
    build_file = "//bazel:openssl.BUILD",
    sha256 = "f89199be8b23ca45fc7cb9f1d8d3ee67312318286ad030f5316aca6462db6c96",
    strip_prefix = "openssl-1.1.1m",
    urls = [
        "https://www.openssl.org/source/openssl-1.1.1m.tar.gz",
        "https://github.com/openssl/openssl/archive/OpenSSL_1_1_1m.tar.gz",
    ],
)

http_archive(
    name = "com_github_aliyun_oss_sdk",
    build_file = "//bazel:aliyun_oss_sdk.BUILD",
    sha256 = "5cb6e840b966c1c05f01260e82967e791da90c641ad932bf42c14bbc5757a18c",
    strip_prefix = "aliyun-oss-cpp-sdk-master",
    urls = ["https://github.com/aliyun/aliyun-oss-cpp-sdk/archive/master.zip"],
)

# http_archive(
#     name = "com_github_baidu_babylon",
#     sha256 = "626c30f7df34dee8b735d8cabd8779ceb1a9274fd73285ec850f522ad36aa7eb",
#     strip_prefix = "babylon-1.1.3",
#     urls = ["https://github.com/baidu/babylon/archive/v1.1.3.tar.gz"],
# )

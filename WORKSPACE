workspace(name = "openai-grpc-server")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_github_grpc_grpc",
    sha256 = "c5ad277fc21d4899f0e23f6f0337d8a2190d3c66c57ca868378be7c7bfa59fec",
    strip_prefix = "grpc-1.64.1",
    urls = ["https://github.com/grpc/grpc/archive/refs/tags/v1.64.1.tar.gz"],
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")

grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")

grpc_extra_deps()

http_archive(
    name = "com_github_googleapis_google_cloud_cpp",
    sha256 = "8d398958cad2338087ed5321db1d2c70a078d5d9d4dde720449395a3365a9ced",
    strip_prefix = "google-cloud-cpp-2.24.0",
    urls = ["https://github.com/googleapis/google-cloud-cpp/archive/refs/tags/v2.24.0.tar.gz"],
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
    sha256 = "3de192da63a6ff90f8a9e5e8d98ab8c7001f18b018889b835b181cd94c1ee735",
    strip_prefix = "openai-server-proto-1.0.9",
    urls = ["https://github.com/pkusunjy/openai-server-proto/archive/v1.0.9.tar.gz"],
)

http_archive(
    name = "com_github_nelhage_rules_boost",
    sha256 = "313e8a82b2423ed99011b0addb8ddbaf243b9b4ef2ab7c635050732eb4cd4015",
    strip_prefix = "rules_boost-8018021402a99302d03e77a7781cd767a8fb00a9",
    urls = ["https://github.com/nelhage/rules_boost/archive/8018021402a99302d03e77a7781cd767a8fb00a9.tar.gz"],
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

# Rule repository, note that it's recommended to use a pinned commit to a released version of the rules
http_archive(
   name = "rules_foreign_cc",
   sha256 = "5303e3363fe22cbd265c91fce228f84cf698ab0f98358ccf1d95fba227b308f6",
   strip_prefix = "rules_foreign_cc-0.9.0",
   url = "https://github.com/bazelbuild/rules_foreign_cc/archive/0.9.0.zip",
)

load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

# This sets up some common toolchains for building targets. For more details, please see
# https://github.com/bazelbuild/rules_foreign_cc/tree/main/docs#rules_foreign_cc_dependencies
rules_foreign_cc_dependencies()

http_archive(
    name = "rules_perl",  # 2021-09-23T03:21:58Z
    sha256 = "cd67b3c262714e2504e28fa71bf23fca5bf27035d225019c44ed70b36939517b",
    strip_prefix = "rules_perl-6d3f98c36e0cb756cb5e34f2d7e8f1053e9506cc",
    urls = [
        "https://github.com/bazelbuild/rules_perl/archive/6d3f98c36e0cb756cb5e34f2d7e8f1053e9506cc.tar.gz",
    ],
)
load("@rules_perl//perl:deps.bzl", "perl_register_toolchains")
perl_register_toolchains()

http_archive(
    name = "openssl",  # 2021-12-14T15:45:01Z
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

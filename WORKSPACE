workspace(name = "openai-grpc-server")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "com_github_curl_curl",
    urls = [
        "https://storage.googleapis.com/cloud-cpp-community-archive/com_github_curl_curl/curl-7.69.1.tar.gz",
        "https://curl.haxx.se/download/curl-7.69.1.tar.gz",
    ],
    strip_prefix = "curl-7.69.1",
    build_file = "//bazel:curl.BUILD",
    sha256 = "01ae0c123dee45b01bbaef94c0bc00ed2aec89cb2ee0fd598e0d302a6b5e0a98",
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
    sha256 = "b5035e07648992c7f19f7755ebf934ec3f499c18132dc9e9783264dfea9b4762",
    strip_prefix = "openai-server-proto-1.1.5",
    urls = ["https://github.com/pkusunjy/openai-server-proto/archive/v1.1.5.tar.gz"],
)

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

workspace(name = "openai-grpc-server")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# for liboai
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
    sha256 = "9eb54a4faea404f2848b06aac321c2d9321f63539e6ffd7e89959c1fdd94c775",
    strip_prefix = "liboai-1.0.14/liboai",
    urls = ["https://github.com/pkusunjy/liboai/archive/v1.0.14.tar.gz"],
)

http_archive(
    name = "com_github_pkusunjy_openai_server_proto",
    sha256 = "ba6ab03d10498ad555f18ca3f2984eec7a65bed238dcd06b62933df56ba090c0",
    strip_prefix = "openai-server-proto-1.1.17",
    urls = ["https://github.com/pkusunjy/openai-server-proto/archive/v1.1.17.tar.gz"],
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

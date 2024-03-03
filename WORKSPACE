workspace(name = 'openai_server')

load('@bazel_tools//tools/build_defs/repo:http.bzl', 'http_archive')

http_archive(
    name = 'com_google_googletest',
    urls = ['https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz'],
    strip_prefix = 'googletest-1.14.0',
    sha256 = '8ad598c73ad796e0d8280b082cebd82a630d73e73cd3c70057938a6501bba5d7',
)

http_archive(
    name = 'com_apache_brpc',
    urls = ['https://github.com/apache/brpc/archive/refs/tags/1.8.0.tar.gz'],
    strip_prefix = 'brpc-1.8.0',
    sha256 = '13ffb2f1f57c679379a20367c744b3e597614a793ec036cd7580aae90798019d',
)

# below are dependencies for brpc
http_archive(
    name = 'bazel_skylib',
    urls = ['https://github.com/bazelbuild/bazel-skylib/releases/download/1.1.1/bazel-skylib-1.1.1.tar.gz'],
    sha256 = 'c6966ec828da198c5d9adbaa94c05e3a1c7f21bd012a0b29ba8ddbccb2c93b0d'
)

# http_archive(
    # name = 'com_github_google_leveldb',
    # urls = ['https://github.com/google/leveldb/archive/refs/tags/1.23.tar.gz'],
    # strip_prefix = 'leveldb-1.23',
    # sha256 = '9a37f8a6174f09bd622bc723b55881dc541cd50747cbd08831c2a82d620f6d76',
# )

http_archive(
    name = 'com_github_google_leveldb',
    build_file = '//:third_party/leveldb.BUILD',
    strip_prefix = 'leveldb-a53934a3ae1244679f812d998a4f16f2c7f309a6',
    url = 'https://github.com/google/leveldb/archive/a53934a3ae1244679f812d998a4f16f2c7f309a6.tar.gz',
    sha256 = '3912ac36dbb264a62797d68687711c8024919640d89b6733f9342ada1d16cda1',
)

http_archive(
  name = 'com_google_protobuf',
  urls = ['https://github.com/protocolbuffers/protobuf/archive/refs/tags/v21.12.tar.gz'],
  strip_prefix = 'protobuf-21.12',
  sha256 = '22fdaf641b31655d4b2297f9981fa5203b2866f8332d3c6333f6b0107bb320de',
)
load('@com_google_protobuf//:protobuf_deps.bzl', 'protobuf_deps')
protobuf_deps()

http_archive(
    name = 'com_github_madler_zlib',  # 2017-01-15T17:57:23Z
    build_file = '//:third_party/zlib.BUILD',
    sha256 = 'c3e5e9fdd5004dcb542feda5ee4f0ff0744628baf8ed2dd5d66f8ca1197cb1a1',
    strip_prefix = 'zlib-1.2.11',
    urls = [
        'https://downloads.sourceforge.net/project/libpng/zlib/1.2.11/zlib-1.2.11.tar.gz',
        'https://zlib.net/fossils/zlib-1.2.11.tar.gz',
    ],
)

http_archive(
    name = 'com_github_gflags_gflags',
    urls = ['https://github.com/gflags/gflags/archive/refs/tags/v2.2.2.tar.gz'],
    strip_prefix = 'gflags-2.2.2',
    sha256 = '34af2f15cf7367513b352bdcd2493ab14ce43692d2dcd9dfc499492966c64dcf',
)

# native.new_local_repository(
    # name = 'openssl',
    # path = '/usr',
    # build_file = '//:openssl.BUILD',
# )

http_archive(
    name = 'openssl',
    build_file = '//:third_party/openssl.BUILD',
    sha256 = 'f89199be8b23ca45fc7cb9f1d8d3ee67312318286ad030f5316aca6462db6c96',
    strip_prefix = 'openssl-1.1.1m',
    urls = [
        'https://www.openssl.org/source/openssl-1.1.1m.tar.gz',
        'https://github.com/openssl/openssl/archive/OpenSSL_1_1_1m.tar.gz',
    ],
)

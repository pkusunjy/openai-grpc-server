load("@rules_foreign_cc//foreign_cc:defs.bzl", "configure_make")

filegroup(
    name = "all_srcs",
    srcs = glob(["**"]),
)

CONFIGURE_OPTIONS = [
    "no-idea",
    "no-mdc2",
    "no-rc5",
    "no-ssl3",
    "no-ssl3-method",
    "enable-rfc3779",
    "enable-cms",
    "no-capieng",
    "enable-ec_nistp_64_gcc_128",
    "--with-zlib-include=$$EXT_BUILD_DEPS$$",
    "--with-zlib-lib=$$EXT_BUILD_DEPS$$",
    # https://stackoverflow.com/questions/36220341/struct-in6-addr-has-no-member-named-s6-addr32-with-ansi
    "-D_DEFAULT_SOURCE=1",
    "-DPEDANTIC",
]

alias(
    name = "ssl",
    actual = "openssl",
    visibility = ["//visibility:public"],
)

alias(
    name = "crypto",
    actual = "openssl",
    visibility = ["//visibility:public"],
)

configure_make(
    name = "openssl",
    configure_command = "config",
    configure_in_place = True,
    configure_options = CONFIGURE_OPTIONS,
    env = select({
        "@platforms//os:macos": {
            "AR": "",
            "PERL": "$$EXT_BUILD_ROOT$$/$(PERL)",
        },
        "//conditions:default": {
            "PERL": "$$EXT_BUILD_ROOT$$/$(PERL)",
        },
    }),
    lib_name = "openssl",
    lib_source = ":all_srcs",
    # Note that for Linux builds, libssl must come before libcrypto on the linker command-line.
    # As such, libssl must be listed before libcrypto
    out_static_libs = [
        "libssl.a",
        "libcrypto.a",
    ],
    targets = [
        "build_libs",
        "install_dev",
    ],
    toolchains = ["@rules_perl//:current_toolchain"],
    deps = [
        "@com_github_madler_zlib//:zlib",
    ],
)

filegroup(
    name = "gen_dir",
    srcs = [":openssl"],
    output_group = "gen_dir",
)

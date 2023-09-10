load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Knitro

load("//bazel:knitro.bzl", "knitro")
knitro(name = "knitro")

# CppAD

http_archive(
   name = "rules_foreign_cc",
   sha256 = "2a4d07cd64b0719b39a7c12218a3e507672b82a97b98c6a89d38565894cf7c51",
   strip_prefix = "rules_foreign_cc-0.9.0",
   url = "https://github.com/bazelbuild/rules_foreign_cc/archive/refs/tags/0.9.0.tar.gz",
)
load("@rules_foreign_cc//foreign_cc:repositories.bzl", "rules_foreign_cc_dependencies")

# This sets up some common toolchains for building targets. For more details, please see
# https://bazelbuild.github.io/rules_foreign_cc/0.9.0/flatten.html#rules_foreign_cc_dependencies
rules_foreign_cc_dependencies(
    cmake_version="3.23.2",
    ninja_version="1.11.0")

git_repository(
    name = "cppad",
    remote = "https://github.com/coin-or/CppAD.git",
    commit = "74e04ec848c590dfccae30318a2f6668306fc314",
    build_file_content = """
load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@rules_foreign_cc//foreign_cc:defs.bzl", "cmake")

package(default_visibility = ["//visibility:public"])

filegroup(
    name = "srcs",
    srcs = glob(["**"]),
    visibility = ["//visibility:public"],
)

# Shows a standard library
cmake(
    name = "cppad",
    lib_source = ":srcs",
    # pass include/version123 to C/C++ provider as include directory
    generate_args = [
        "-Dcppad_static_lib=TRUE",
    ],
    out_lib_dir = "../cppad.build_tmpdir/cppad_lib/",
    out_static_libs = ["libcppad_lib.a"],
    out_include_dir = "include/",
)
""",
)

// The wasi-sdk does not include libstdc++ or libc++ by default. 
// Instead, it provides the necessary environment for compiling C/C++ code to WebAssembly. 
// We need to ensure that we are correctly configuring the build to use the C++ standard library available in wasi-sdk.
//
//  The cargo:rustc-link-lib=static=c++ and cargo:rustc-link-lib=static=c++abi lines 
// ensure that the static versions of the C++ standard library and C++ ABI library are linked.

use std::env;
use std::path::PathBuf;

fn main() {
    let target = env::var("TARGET").unwrap();
    if target.contains("wasm32") {
        let wasi_sdk_path = env::var("WASI_SDK_PATH").expect("WASI_SDK_PATH not set");
        let sysroot = PathBuf::from(&wasi_sdk_path).join("share/wasi-sysroot");
        let include_path = sysroot.join("include");
        let lib_path = sysroot.join("lib/wasm32-wasi");

        // Path to the installed libsodium-wasi
        let sodium_include_path = PathBuf::from("/libsodium/zig-out/include");
        let sodium_lib_path = PathBuf::from("/libsodium/zig-out/lib ");

        println!("cargo:rustc-link-search=native={}", lib_path.display());
        println!("cargo:rustc-link-lib=static=c++");
        println!("cargo:rustc-link-lib=static=c++abi");
        //println!("cargo:rustc-link-lib=static=sodium");

        cc::Build::new()
            // .cpp(true) // this will cause rust-lld: error: unable to find library -lstdc++
            .file("cpp/my_code.cpp")
            .file("cpp/blake3/blake3.c")
            .file("cpp/blake3/blake3_dispatch.c")
            .file("cpp/blake3/blake3_portable.c")
            .file("cpp/blake3/blake3.c")
            .file("cpp/crypto/hashing.cpp")
            .file("cpp/utils/base58.cpp")
            .include(include_path)
            .include(sodium_include_path)
            .flag("--sysroot")
            .flag(sysroot.to_str().unwrap())
            .flag("-fno-exceptions") // By adding the -fno-exceptions flag to the cc::Build configuration, you ensure that the C++ code is compiled without exception support, preventing the linker errors related to __cxa_allocate_exception. More info https://github.com/WebAssembly/wasi-sdk?tab=readme-ov-file#notable-limitations
            .compile("my_code");
    } else {
        cc::Build::new()
            // .cpp(true)
            .file("cpp/my_code.cpp")
            .compile("my_code");
    }
    println!("cargo:rerun-if-changed=cpp/my_code.cpp");
}
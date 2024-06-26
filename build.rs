// // export WASI_SDK_PATH=~/Downloads/wasi-sdk-22.0
// // export WASI_SYSROOT=$WASI_SDK_PATH/share/wasi-sysroot

use std::env;
use std::path::PathBuf;

fn main() {
    let target = std::env::var("TARGET").unwrap();
    if target.contains("wasm32") {
        println!("cargo:rustc-link-search=native={}/share/wasi-sysroot/lib/wasm32-wasi", env!("WASI_SDK_PATH"));
        println!("cargo:rustc-link-lib=static=c++");
        
        cc::Build::new()
            // .cpp(true)
            // .flag("-std=c++17") // Use the appropriate C++ standard
            .file("cpp/my_code.cpp")
            .include(format!("{}/share/wasi-sysroot/include", env!("WASI_SDK_PATH")))
            .flag("--sysroot")
            .flag(&format!("{}/share/wasi-sysroot", env!("WASI_SDK_PATH")))
            .compile("my_code");
    } else {
        cc::Build::new()
            .cpp(true)
            .file("cpp/my_code.cpp")
            .compile("my_code");
    }
    println!("cargo:rerun-if-changed=cpp/my_code.cpp");
}

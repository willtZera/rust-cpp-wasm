// // export WASI_SDK_PATH=~/Downloads/wasi-sdk-22.0
// // export WASI_SYSROOT=$WASI_SDK_PATH/share/wasi-sysroot

// use std::env;
// use std::path::PathBuf;

// fn main() {
//     let wasi_sdk_path = env::var("WASI_SDK_PATH").expect("Please set the WASI_SDK_PATH environment variable");

//     let sysroot = PathBuf::from(&wasi_sdk_path).join("share/wasi-sysroot");

//     cc::Build::new()
//         .cpp(true)
//         .compiler(PathBuf::from(&wasi_sdk_path).join("bin/clang++"))
//         .file("src/hello.cpp")
//         .flag("--sysroot")
//         .flag(sysroot.to_str().unwrap())
//         .compile("hello");

//     println!("cargo:rustc-link-search=native={}/lib", sysroot.to_str().unwrap());
//     println!("cargo:rustc-link-lib=stdc++");
// }

fn main() {
    cc::Build::new()
        .cpp(true)
        .file("cpp/my_code.cpp")
        .compile("my_code");
    println!("cargo:rerun-if-changed=cpp/my_code.cpp");
}
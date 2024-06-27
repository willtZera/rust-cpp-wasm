# Overview

A rust project with C++ code compatible with wasm

## Prerequisites 


1. Download and install `wasi-sdk` from the official [GitHub repository](https://github.com/WebAssembly/wasi-sdk/releases). Choose the appropriate version for your system.
2. After downloading, extract the `wasi-sdk` package and set up the environment variables:
```
export WASI_SDK_PATH=/path/to/wasi-sdk
export PATH=$WASI_SDK_PATH/bin:$PATH
```
3. You may also need to install `rustup`

## Build

```
cargo build --target=wasm32-wasi --release
```

## Run 

```
wasmedge --reactor target/wasm32-wasi/release/my_rust_app.wasm test
```

This should print the following:

```
[test] Hello from Rust
[hello] Hello, World from C++! (std::cout)
[hello] Hello World from C++! (printf)
```

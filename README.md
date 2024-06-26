# Overview

A rust project with C++ code compatible with wasm


## Build

```
cargo build --target=wasm32-wasi --release
```

## Run 

```
wasmedge --reactor  my_rust_app.wasm hello
wasmedge my_rust_app.wasm
```

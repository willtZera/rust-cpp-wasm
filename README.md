# Overview

A rust project with C++ code compatible with wasm


## Build

```
cargo build --target=wasm32-wasi --release
```

## Run 

```
wasmedge --reactor  hello.wasm hello
wasmedge hello.wasm
```

# Base image
FROM ubuntu:22.04

# Update package repository and install dependencies
RUN apt-get update && apt-get upgrade -y && apt-get install -y \
    build-essential \
    ccache \
    curl \
    wget \
    clang \
    cmake \
    git \
    libssl-dev && \
    apt-get clean

# Install Rust
RUN curl https://sh.rustup.rs -sSf | sh -s -- -y
ENV PATH="/root/.cargo/bin:${PATH}"
RUN rustup target add wasm32-wasi

# Download and extract WASI SDK
RUN wget https://github.com/WebAssembly/wasi-sdk/releases/download/wasi-sdk-22/wasi-sdk-22.0-linux.tar.gz && \
    tar -xvzf wasi-sdk-22.0-linux.tar.gz && \
    mv wasi-sdk-22.0 /opt/wasi-sdk

# Set environment variables for WASI SDK
ENV WASI_SDK_PATH=/opt/wasi-sdk
ENV PATH="${WASI_SDK_PATH}/bin:${PATH}"
ENV CFLAGS="-I${WASI_SDK_PATH}/share/wasi-sysroot/include"
ENV LDFLAGS="-L${WASI_SDK_PATH}/share/wasi-sysroot/lib"

# Copy the project files
COPY . /my_rust_project
WORKDIR /my_rust_project

# Build the Rust project
RUN cargo build --target=wasm32-wasi --release

# Install WasmEdge
RUN wget https://github.com/WasmEdge/WasmEdge/releases/download/0.11.0/WasmEdge-0.11.0-manylinux2014_x86_64.tar.gz && \
    tar -xvzf WasmEdge-0.11.0-manylinux2014_x86_64.tar.gz && \
    cp -r WasmEdge-0.11.0-Linux/include/wasmedge /usr/local/include/ && \
    cp WasmEdge-0.11.0-Linux/bin/wasmedge /usr/local/bin/ && \
    cp WasmEdge-0.11.0-Linux/bin/wasmedgec /usr/local/bin/ && \
    cp WasmEdge-0.11.0-Linux/lib64/libwasmedge.so /usr/local/lib/ && \
    cp WasmEdge-0.11.0-Linux/lib64/libwasmedge.so.0 /usr/local/lib/ && \
    rm -f /usr/local/lib/libwasmedge.so.0 && \
    ln -s /usr/local/lib/libwasmedge.so /usr/local/lib/libwasmedge.so.0

# Set the library path
ENV LD_LIBRARY_PATH="/usr/local/lib:${LD_LIBRARY_PATH}"

# Run the application
CMD ["wasmedge", "--reactor", "target/wasm32-wasi/release/my_rust_app.wasm", "test"]

rm -rf libsodium
git clone https://github.com/jedisct1/libsodium.git
cd libsodium
./autogen.sh -s
zig build -Dtarget=wasm32-wasi

# libsodium/zig-out/include will contain headers
# libsodium/zig-out/lib will contain binaries
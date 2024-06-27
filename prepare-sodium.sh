export WASI_SDK_PATH=~/Downloads/wasi-sdk-22.0
export WASI_SYSROOT="$(cd $WASI_SDK_PATH/share/wasi-sysroot && pwd)"
export PATH=$WASI_SDK_PATH/bin:$PATH

rm -rf libsodium
git clone https://github.com/jedisct1/libsodium.git

cd libsodium
git checkout stable

mkdir -p wasm-build
PREFIX=$(cd wasm-build && pwd)

./autogen.sh
./configure --prefix="${PREFIX}" \
  --with-sysroot="$WASI_SYSROOT" \
  --host=wasm32-wasi \
  --disable-ssp --enable-static --disable-shared 

make
make install

# libsodium/wasm-build/include will contain headers
# libsodium/wasm-build/lib will contain binaries
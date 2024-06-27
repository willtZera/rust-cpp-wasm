cmake_minimum_required(VERSION 3.10)
project(hash_functions)

set(CMAKE_CXX_STANDARD 17)

# Set the path to the libsodium WASI installation
set(LIBSODIUM_WASI_PATH "/opt/libsodium-wasi")

# Include directories
include_directories(${LIBSODIUM_WASI_PATH}/include)

# Add the blake3 source files
add_library(blake3 STATIC ../blake3/blake3.c)

# Add the hash_functions source files
add_library(hash_functions STATIC hash_functions.cpp)

# Link against libsodium
target_link_libraries(hash_functions ${LIBSODIUM_WASI_PATH}/lib/libsodium.a blake3)

# Add executable for testing (optional)
add_executable(hash_test main.cpp)
target_link_libraries(hash_test hash_functions)

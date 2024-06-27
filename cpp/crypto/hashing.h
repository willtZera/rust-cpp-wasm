#pragma once

#include <cstdint>
//#include <sodium.h>
#include <string>
#include <vector>
#include <iostream>

#include "../blake3/blake3.h"

std::vector<uint8_t> blake3_hash(const std::vector<uint8_t> &input);
std::vector<uint8_t> sha256_hash(const std::vector<uint8_t> &input);
std::vector<uint8_t> sha512_hash(const std::vector<uint8_t> &input);

std::string blake3_hash_c(const std::string &input_str);
std::string sha256_hash_c(const std::string &input_str);
std::string sha512_hash_c(const std::string &input_str);
bool compare_hash_c(const std::string &hash_1_str, const std::string &hash_2_str);
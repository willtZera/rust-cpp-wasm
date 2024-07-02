#include "hashing.h"

std::vector<uint8_t> blake3_hash(const std::vector<uint8_t> &input)
{
    std::vector<uint8_t> hash(BLAKE3_OUT_LEN);
    blake3_hasher hasher;
    blake3_hasher_init(&hasher);
    blake3_hasher_update(&hasher, input.data(), input.size());
    blake3_hasher_finalize(&hasher, hash.data(), hash.size());
    return hash;

}
std::vector<uint8_t> sha256_hash(const std::vector<uint8_t> &input)
{
    std::vector<uint8_t> hash(crypto_hash_sha256_BYTES);
    crypto_hash_sha256(hash.data(), input.data(), input.size());
    return hash;
}

std::vector<uint8_t> sha512_hash(const std::vector<uint8_t> &input)
{
    std::vector<uint8_t> hash(crypto_hash_sha512_BYTES);
    crypto_hash_sha512(hash.data(), input.data(), input.size());
    return hash;
}

std::string blake3_hash_c(const std::string &input_str)
{
    std::vector<uint8_t> input(input_str.begin(), input_str.end());
    std::vector<uint8_t> hash(BLAKE3_OUT_LEN);
    blake3_hasher hasher;
    blake3_hasher_init(&hasher);
    blake3_hasher_update(&hasher, input.data(), input.size());
    blake3_hasher_finalize(&hasher, hash.data(), hash.size());
    std::string hash_str(hash.begin(), hash.end());
    return hash_str;
}

std::string sha256_hash_c(const std::string &input_str)
{
    std::vector<uint8_t> input(input_str.begin(), input_str.end());
    std::vector<uint8_t> hash(crypto_hash_sha256_BYTES);
    crypto_hash_sha256(hash.data(), input.data(), input.size());
    std::string hash_str(hash.begin(), hash.end());
    return hash_str;
}

std::string sha512_hash_c(const std::string &input_str)
{
    std::vector<uint8_t> input(input_str.begin(), input_str.end());
    std::vector<uint8_t> hash(crypto_hash_sha512_BYTES);
    crypto_hash_sha512(hash.data(), input.data(), input.size());
    std::string hash_str(hash.begin(), hash.end());
    return hash_str;
}
bool compare_hash_c(const std::string &hash_1_str, const std::string &hash_2_str)
{
    std::vector<uint8_t> hash_1(hash_1_str.begin(), hash_1_str.end());
    std::vector<uint8_t> hash_2(hash_2_str.begin(), hash_2_str.end());

    if (hash_1.size() != hash_2.size())
    {
        return false;
    }

    int hash_size = static_cast<int>(hash_1.size());

    for (int x = 0; x < hash_size; x++)
    {
        if (hash_1.at(x) != hash_2.at(x))
        {
            return false;
        }
    }
    return true;
}
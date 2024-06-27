#include <iostream>
#include <string>
#include "crypto/hashing.h"
#include "utils/base58.h"

extern "C"
{
  void hello()
  {
    std::string str = "World";
    std::string test = blake3_hash_c(str);
    std::string encoded = base58_encode(test);
    const char *cstr = encoded.c_str();
    std::cout << "[hello] Hello, " << str << " from C++! (std::cout)" << std::endl;
    std::cout << encoded << std::endl;
    printf("[hello] Hello %s from C++! (printf)\n", cstr);
  }
}
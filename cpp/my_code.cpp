#include <iostream>
#include <string>
#include "crypto/hashing.h"
#include "utils/base58.h"

extern "C"
{ 
  void hello()
  {
    if (sodium_init() < 0)
    {
      /* panic! the library couldn't be initialized; it is not safe to use */
      printf("ERROR: the sodium couldn't be initialized!\n");
      return;
    }
    std::string str = "World";
    std::string test = blake3_hash_c(str);
    std::string test1 = sha256_hash_c(str);
    std::string encoded = base58_encode(test);
    std::string encoded1 = base58_encode(test1);
    std::cout << "blake3: " << encoded << std::endl;
    std::cout << "sha256: " << encoded1 << std::endl;
  }
}
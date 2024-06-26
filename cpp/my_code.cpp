#include <iostream>
#include <string>

extern "C"
{
  void hello()
  {
    std::string name = "World";
    std::cout << "Hello, " << name << " from C++!" << std::endl;
  }
}
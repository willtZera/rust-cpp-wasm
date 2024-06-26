#include <iostream>
#include <string>

extern "C"
{
  void hello()
  {
    std::string str = "World";
    const char *cstr = str.c_str();
    std::cout << "[hello] Hello, " << str << " from C++! (std::cout)" << std::endl;
    printf("[hello] Hello %s from C++! (printf)\n", cstr);
  }
}
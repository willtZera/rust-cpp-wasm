#include <iostream>
#include <string>

extern "C"
{
  void hello()
  {
    std::string str = "World";
    const char *cstr = str.c_str();
    std::cout << "Hello, " << str << " from C++!" << std::endl;
    printf("Hello from C++, %s \n", cstr);
  }
}
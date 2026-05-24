#include "extern_template.h"
#include <cstdio>
#include <string>

// this function which calls this instantiation, which is done somewhere else
void func(const std::string &str) {
  std::cout << "func() printing " << str << ": ";
  print(std::cout, str);
}

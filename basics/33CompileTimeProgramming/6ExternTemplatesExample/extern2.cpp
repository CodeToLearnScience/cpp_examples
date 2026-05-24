#include "extern_template.h"

// we have our main func which calls the instantiation, which is done somewhere
// else
int main() {
  std::string str{"Hello"};
  std::cout << "main() printing Hello: " << str;
  std::cout << "\n";
  print(std::cout, str);
  func(str);
  std::cout << std::endl;
}

#include "6ExternTemplates.h"
#include <fstream>
#include <ostream>

// define the template in one source file only
template <typename T> std::ostream &print(std::ostream &os, const T &t) {
  return os << t;
}

// manual instantiation of the template
template std::ostream &print(std::ostream &os, const std::string &str);

int main() {

  std::string str{"Hello"};
  std::cout << "main() printing " << str << ": ";
  print(std::cout, str);
  std::cout << "\n";
  func(str);
  std::cout << "\n";
}

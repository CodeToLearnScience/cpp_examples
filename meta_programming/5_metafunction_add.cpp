#include <iostream>

template <int a, int b> struct Add_ { constexpr static int value = a + b; };

template <int a, int b> constexpr int Add = a + b;

auto main() -> int {

  std::cout << Add_<3, 4>::value << "\t" << Add<5, 6> << "\n";

  return 0;
}
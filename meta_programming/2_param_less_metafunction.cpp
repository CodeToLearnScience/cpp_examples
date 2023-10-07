#include <iostream>

struct Fun {
  using type = int;
};

constexpr int fun() { return 10; }

/// using constexpr
template <int a> constexpr int fun = a + 1;

auto main() -> int { std::cout << fun<4> << std::endl; }
#include <iostream>

template <typename T> struct Fun_ { using type = T; };

template <> struct Fun_<int> {
  using reference_type = int &;
  using const_reference_type = const int &;
  using value_type = int;
};

auto main() -> int {}
#include <iostream>
#include <type_traits>

// auto wrap1(bool check) {
//   if (check)
//     return (int)0;
//   else
//     return (double)0;
// }

// But at compile time, we can break this limitation in some way:
template <bool check, std::enable_if_t<check> * = nullptr> auto fun() {
  return (int)0;
}

template <bool check, std::enable_if_t<!check> * = nullptr> auto fun() {
  return (double)1.0;
}

template <bool check> auto wrap2() { return fun<check>(); }

/// simplify codes with constexpr in C++17
template <bool check> auto fun1() {
  if constexpr (check) {
    return (int)0;
  } else {
    return (double)1.0;
  }
}

auto main() -> int {
  std::cerr << wrap2<true>() << std::endl;
  std::cerr << fun1<false>() << std::endl;
}
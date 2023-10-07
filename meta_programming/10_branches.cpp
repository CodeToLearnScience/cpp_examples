#include <iostream>
#include <type_traits>

template <bool B, typename T, typename F> struct conditional {
  using type = T;
};

template <typename T, typename F> struct conditional<false, T, F> {
  using type = F;
};

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

std::conditional<true, int, float>::type h = 3;
std::conditional<false, int, float>::type f = 3.0f;
#include <iostream>
#include <type_traits>

template <bool AddorRemoveRef> struct Fun_;

template <> struct Fun_<true> {
  template <typename T> using type = std::add_lvalue_reference<T>;
};

template <> struct Fun_<false> {
  template <typename T> using type = std::remove_reference<T>;
};

template <typename T> using Res_ = Fun_<false>::template type<T>;

Res_<int &>::type h = 3;

/**
 *  The above example can be written mathematically as follows
 * Fun(addOrRemove) = T
 * addOrRemove is value of type bool, while T is the output of Fun_ and T is
 * also a Metafunction
 */

auto main() -> int {
  std::cout << h << "\n";
  return 0;
}
#include <iostream>

template <typename T> struct Fun_ { using type = T; };

template <> struct Fun_<int> { using type = unsigned int; };

template <> struct Fun_<long> { using type = unsigned long; };

/**we can introduce another definition on the basis of Fun_,
 * so as to construct another metafunction Fun*/
template <typename T> using Fun = typename Fun_<T>::type;

auto main() -> int {

  Fun_<int>::type h = 3;
  return 0;
}
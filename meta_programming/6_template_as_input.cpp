#include <iostream>

template <template <typename> class T1, typename T2> struct Fun_ {
  using type = typename T1<T2>::type;
};

template <template <typename> class T1, typename T2>
using Fun = typename T1<T2>::type;

/// The above template metafunctions can be viewed as Function of function
/// and parameter.
/// Fun(T1, t2) = T1(t2)
auto main() -> int {
  Fun<std::remove_reference, int &> h = 3;
  std::cout << h << "\n";
  return 0;
}
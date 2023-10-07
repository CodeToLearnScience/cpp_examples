#include <iostream>

/// recursive call
template <int N> constexpr std::size_t OnesCount = (N % 2) + OnesCount<N / 2>;
/// to end loop
template <> constexpr std::size_t OnesCount<0> = 0;

////////////////////
/// Working with arrays
template <std::size_t... N> constexpr std::size_t Accumulate = 0;

template <std::size_t curInput, std::size_t... N>
constexpr std::size_t Accumulate<curInput, N...> = curInput + Accumulate<N...>;

/// C++ 17 fold expression technique for summation
template <std::size_t... N> constexpr std::size_t fun() {
  return (0 + ... + N);
}

auto main() -> int {
  std::cout << OnesCount<45> << std::endl;
  std::cout << Accumulate<1, 2, 3, 4, 5> << std::endl;
  std::cout << fun<1, 2, 3, 4, 5>() << std::endl;
  return 0;
}
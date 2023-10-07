#include <iostream>
#include <type_traits>

std::remove_reference<int &>::type h1 = 3;
std::remove_reference_t<int &> h2 = 3;
auto main() -> int {}
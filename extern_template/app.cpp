#include "foo.h"
#include <iostream>

int main() {

  /// explicit instantiation
  std::cout << sum((int)5, (int)3) << "\n";

  /// explicit instantiation
  std::cout << sum((double)5.0, (double)3.0) << "\n";

  /// implicit instantiation
  std::cout << sum(8u, 1u) << "\n";

  /// implicit instantiation
  std::cout << sum(5.1f, 3.2f) << "\n";
}

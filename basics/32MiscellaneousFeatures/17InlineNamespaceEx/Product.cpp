#include <iostream>
#include <string>

namespace product {
#include "Version1.h"
#include "Version2.h"

void test() {
  refrigerator fridge;
  fridge.print();
  std::cout << "\n";
}

} // namespace product

int main() { product::test(); }

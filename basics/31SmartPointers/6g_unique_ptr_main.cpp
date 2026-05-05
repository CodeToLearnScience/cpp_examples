#include "6e_unique_ptr_Date.h"
#include <iostream>

int main() {
  // Date_impl date(16, 11, 2019); //if we try to use this constructor directly
  Date date(16, 11, 2019);
  date.print();
  std::cout << "\n";
  date.set_day(17);
  date.print();
  std::cout << "\n";
}

#include <iostream>
#include <vector>

extern "C" {
#include "12c_array.h"
}

using namespace std;

int main() {
  vector<int> vec{3, 1, 4, 1, 5, 9};
  cout << "Calling array_print(): ";
  array_print(vec.data(), vec.size());
}

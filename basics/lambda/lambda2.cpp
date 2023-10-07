#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>


int main(){

  std::vector<int> values {0,1,2,3,4,5};

  auto it = std::find_if(values.begin(), values.end(), [](int value) {return value > 3;});
  std::cout << *it << std::endl;

  return 0;
}

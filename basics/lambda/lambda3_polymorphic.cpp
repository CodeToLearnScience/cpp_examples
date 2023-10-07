#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>


int main(){

  int n = 40.;


  auto it = [](auto &value)->auto {return 3*value;};
  
  auto x = it(n);
  std::cout << "type of x: " << typeid(x).name() << std::endl;

  return 0;
}

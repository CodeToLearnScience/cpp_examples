#include <stdio.h>
#include <iostream>
#include <vector>


void for_each(const std::vector<int>& values, void(*func)(int))
{
  for (int value : values)
    func(value);
}

int main(){

  std::vector<int> values {0,1,2,3,4,5};

  auto lambda = [](int value) {std::cout << "value: " << value << "\n";};
  for_each(values, lambda);
  std::cin.get();

  return 0;
}

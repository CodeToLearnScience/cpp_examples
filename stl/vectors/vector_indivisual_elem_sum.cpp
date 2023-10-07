#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
  std::vector<int> v(10);
  int sum = 0;

  for (int i = 0; i < 10; i++) {
    for (auto &elem : v) {
      elem += 2;
    }
  }

  for (auto &elem : v) {
    std::cout << elem << "\n";
  }

  return 0;
}
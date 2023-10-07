#include <algorithm>
#include <array>
#include <iostream>
#include <vector>

struct vars {
  int x;
  double y;

  std::array<int, 5> tks{1, 2, 3, 4, 5};

  double get_xy() { return x * y; }
};

int main(int argc, char const *argv[]) {
  std::vector<int> v(10);
  std::vector<int> w(10);
  int sum = 0;

  for (std::size_t i = 0; i < v.size(); i++) {
    w[i] += 20;
  }

  for (auto &elem : w) {
    std::cout << elem << "\n";
  }

  std::vector<vars> vars_vec(10);

  for (std::size_t i = 0; i < vars_vec.size(); i++) {
    vars_vec[i].x = i;
    vars_vec[i].y = i * 2.0;
    for (auto &elem : vars_vec[i].tks) {
      elem += 10;
    }
  }

  return 0;
}
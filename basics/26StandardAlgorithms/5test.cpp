#include <algorithm>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

using namespace std;

int main() {

  vector<int> vec{1, 2, 3, 4, 5};
  for (auto v : vec) {
    cout << v << ", ";
  }
  cout << "\n";

  sort(begin(vec), end(vec));
  // std::ranges::sort(vec);
  for (auto v : vec) {
    cout << v << ", ";
  }

  sort(begin(vec), end(vec), [](int a, int b) { return (a > b); });
  // ranges::sort(vec, [](int a, int b) { return (a > b); }); //-std=c++2a

  cout << "\n";
  for (auto v : vec) {
    cout << v << ", ";
  }
}

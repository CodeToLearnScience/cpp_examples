#include <iostream>

using namespace std;

int main() {
  int y = 1;
  auto res = [y = y + 1](int x) { return x + y; };
  cout << y << "\n";
  cout << res(5) << "\n";
}

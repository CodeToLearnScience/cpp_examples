/* -------------------------
 shuffle() Algorithm
-------------------------
- In fact, there is only one random number algorithm in the library shuffle(),
which is shuffle() rearranges an iterator range in a random order
- It takes a random number engine as its third argument and puts the elements
of iterator in random range

  vector<int> vec{3,1,4,1,5,9};
  static mt19937 mt;
  shuffle(begin(vec), end(vec), mt);

- shuffle() calls uniform_int_distribution internally
- It gives perfect shuffling - all permutations are equally likely
- random_shuffle() uses rand() and it deprecated
------------------------------------
std::bernoulli_distribution
------------------------------------
- Uniform distribution will give a range of integers or reals, which are equally
likely
- bernoulli_distribution rescales a sequence of numbers into boolean values
- This is useful for making one-off decision with random outcomes. Which are
50-50 like tossing a coin

-------------------------
shuffle implementation
-------------------------
- We can implement shuffle by swapping elements at random
  std::swap(vec[i], vec[i_random]);
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <random>
#include <vector>

using namespace std;

void print(const vector<int> &vec) {
  ostream_iterator<int> oi(cout, ", ");
  copy(vec.begin(), vec.end(), oi);
}

int main() {
  vector<int> vec{3, 1, 4, 1, 5, 9};
  static mt19937 mt;

  cout << "Vector before shuffling: ";
  for (auto v : vec) {
    cout << v << " ";
  }
  cout << "\n";

  shuffle(begin(vec), end(vec), mt);

  cout << "Vector after shuffling: ";
  for (auto v : vec) {
    cout << v << " ";
  }
  cout << "\n";

  static bernoulli_distribution bd;
  if (bd(mt)) {
    cout << "Your subjects are greatful for your wise and benevolent rule\n";
  } else {
    cout << "The peasants are revolting\n";
  }

  // demonstrating shuffle implementation
  vector<int> vec1{3, 1, 4, 1, 5, 9};
  cout << "Vector before shuffling with our implementation\n";
  print(vec);
  uniform_int_distribution<int> uid(0, vec1.size() - 1);
  for (int i = 0; i < vec.size(); ++i) {
    std::swap(vec[i], vec[uid(mt)]);
  }
  cout << "\nVector after shuffling with our implementation\n";
  print(vec1);
  cout << "\n";
}

/* We use this implement functional programming in C++
  - C++ classes can define a function call operator
  - C++ class which implements a function call operator called a "functor"

  -----------------------------
  Function call Operator Summary
  -----------------------------
  Prototype
   - some_type operator()(...);

  How to invoke it
   - test(...);

  Called as
   - test.operator()(...);
---------------------
 Functors with state
---------------------
- Functors are calsses, so they could contain member functions and data members
- To keep things simple, they should only be used to "wrap" functions
- They can howver have data members to store values which need to be kept
  between function calls
  * This is known as "state"
 */

#include <iostream>
#include <vector>

using namespace std;

class evenp { // class with function call operator

public:
  bool operator()(int n) { return (n % 2 == 0); } // out function call operator
};

void do_it(const vector<int> &vec, evenp is_even) {
  for (auto v : vec) {
    if (is_even(v)) {
      cout << v << " is even\n";
    }
  }
}

class divisible {

private:
  int divisor{1};

public:
  divisible(int d) : divisor(d) {}

  bool operator()(int n) const { return (n % divisor == 0); }
};

void do_it(const vector<int> &vec, divisible is_div) {
  for (auto v : vec) {
    if (is_div(v)) {
      std::cout << v << " is divisible\n";
    }
  }
}

int main() {
  evenp is_even;    // create a functor object
  if (is_even(6)) { // call its function call operator with argument 6
    cout << " 6 is an even number\n";
  }

  vector<int> numbers{1, 4, 5, 11, 12, 23, 36};

  cout << "Vector: ";
  for (auto number : numbers) {
    cout << number << ", ";
  }
  cout << "\n";

  do_it(numbers, is_even); // pass functor to the vector

  // create a divisible object with member variable equal to 3
  cout << "Finding elements which are divisible by 3\n";
  divisible divisible_by_three{3};
  // pass this as argument to the function call
  do_it(numbers, divisible_by_three);
}

/*-------------------------
  Library Function Objects
  -------------------------
- The C++ library provides some function objects
- These are generic operators for arithmetic, logical and relational operations
- They are implemented as templated functors

-------------------
Less-than operator
-------------------
//pseudo code for less-than operator
template <typename T>
class less{
 public:
  bool operator()(T arg1, T arg2){
    return arg1 < arg2;
  }
};

//use less-than operator as predicate for std::sort()
vector<string> names={"Dilbert", "PHB", "Dogbert", "Asok", "Ted", "Alice",
 "Wally"};
sort(begin(names), end(names), less<string>()); //pass an object of the functor


--------------------
Arithmetic Operators
--------------------
- std::plus x + y
- std::minus x-y
- std::multiplies x*y
- std::divides x/y
- std::modulus x%y
- std::negate -x

----------------------
Relational Operators
----------------------
- std::equal_to x==y
- std::not_equal_to x!=y
- std::greater x>y
- std::less x<y
- std::greater_equal x>=y
- std::less_equal x<=y

-----------------------------
Logical and Bitwise operators
-----------------------------
- std::logical_and x&&y
- std::logical_or x||y
- std::logical_not !x

- std::bit_and x&y
- std::bit_or x|y
- std::bit_xor x^y
- std::bit_not ~x (C++14)
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector<string> names = {"Dilbert", "PHB",   "Dogbert", "Asok",
                          "Ted",     "Alice", "Wally"};
  cout << "Vector before sort()\n";
  for (const auto &name : names) {
    cout << name << ", ";
  }
  cout << "\n" << "\n";

  // sort the data in alphabetical order
  // sort(begin(names), end(names), less<string>());
  sort(begin(names), end(names), greater<string>());

  cout << "Sorted alphabetically\n";
  for (const auto &name : names) {
    cout << name << ", ";
  }
}

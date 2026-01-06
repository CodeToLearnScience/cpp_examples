/*-----------
 * Predicates
 * ----------
 - Many algorithms call a function on each element which returns bool
   * find() calls the operator == for each element to compare it to the target
     value
 - This is known as a "predicate". i.e., the function which returns a bool, is
   known as predicate
 - These algorithms allow us to supply our own predicate
 - We can pass a callable object as an optional extra argument to the algorithm
   call
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

// define a predicate function
bool is_shorter(const string &lhs, const string &rhs) {
  return lhs.size() < rhs.size();
}

// we can also define predicate as a functor
class is_shorter1 {
public:
  // overload () operator
  // takes two strings as arguments
  // returns true or false depending on relative string length
  bool operator()(const string &lhs, const string &rhs) {
    return lhs.size() < rhs.size();
  }
};

int main() {
  vector<string> names = {"Dilbert", "PHB",   "Dogbert", "Asok",
                          "Ted",     "Alice", "Wally"};
  cout << "Vector before sort()\n";
  for (const auto &name : names) {
    cout << name << ", ";
  }
  cout << "\n" << "\n";

  // sort the data in alphabetical order
  sort(begin(names), end(names));

  cout << "Sorted alphabetically\n";
  for (const auto &name : names) {
    cout << name << ", ";
  }

  cout << "\n \n";

  // sort the data by passing the function pointer as the predicate
  sort(begin(names), end(names), is_shorter);
  cout << "Sorted by length\n";
  for (const auto &name : names) {
    cout << name << ", ";
  }

  cout << "\n\n";

  // sort the data by passing the functor as the predicate
  // is_shorter1() a constructor and this creates a temporary object and sort()
  // will call the member function overloaded by operator ()
  sort(begin(names), end(names), is_shorter1());
  cout << "Sorted by length\n";
  for (const auto &name : names) {
    cout << name << ", ";
  }
}

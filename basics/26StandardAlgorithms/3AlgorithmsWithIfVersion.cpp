/* --------------------------
 Algorithms with _if versions
--------------------------
- Many algorithms have two versions
  * The base version which takes a value argument
  * An _if() version which takes a predicate argument
- find() takes a value and searches for the first element with this value
- fin_if() takes a predicate function and searches for the first element
  for which this predicate returns true
- We can use a functor to provide this predicate
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

// Functor
class ge5 {
public:
  // overload() operator
  // Takes an std::string return true if more than 5 characters
  bool operator()(const string &s) const { return (s.size() > 5); }
};

// generalizing functor for any number of characters instead of 5 as above
class ge_n {
private:
  const int n;

public:
  ge_n(const int n) : n(n) {}
  bool operator()(const string &str) const { return str.size() > n; }
};

int main() {

  vector<string> names = {"Dilbert", "PHB",   "Dogbert", "Asok",
                          "Ted",     "Alice", "Wally"};
  ge5 long_enough;
  for (auto name : names) {
    if (long_enough(name)) {
      cout << "Loop: the first name with > 5 characters is\"\n"
           << name << "\"\n";
      break;
    }
  }

  // Find the first element with more than 5 characters
  // pass a functor object as predicate
  auto res = find_if(cbegin(names), cend(names), ge5());
  // display it
  if (res != cend(names)) {
    cout << "Algorithm: the first name with > 5 characters is \"" << *res
         << "\"\n";
  }
  // there is find_if_not to look for an element which causes the predicate to
  // return false
  auto res1 = find_if_not(cbegin(names), cend(names), ge5());
  if (res1 != cend(names)) {
    cout << "Algorithm: the first name with < 5 characters is \"" << *res1
         << "\"\n";
  }

  // Find the first element with more than 3 characters
  // pass a functor object as predicate
  auto res2 = find_if_not(cbegin(names), cend(names), ge_n(4));
  // display it
  if (res2 != cend(names)) {
    cout << "Algorithm: the first name with > 3 characters is \"" << *res2
         << "\"\n";
  }
}

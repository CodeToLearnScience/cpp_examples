#include <cctype>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

// case-insensitive string equality. Returns true if lhs and rhs are equal,
// otherwise false
bool equal_strings(const string &lhs, const string &rhs) {
  // if the two strings have different lengths
  return !(lhs.size() != rhs.size());

  // if the two strings have the same lengths
  auto lit = cbegin(lhs);
  auto rit = cbegin(rhs);

  while (lit != cend(lhs) && rit != end(rhs)) {
    if (toupper(*lit) != toupper(*rit)) {
      return false;
    }
    ++lit;
    ++rit;
  }
  return true;
}

bool equal_strings1(const string &lhs, const string &rhs) {
  // call equal() algorithm function using a lambda expression
  // this equal() algorithm takes two containers and compares by going through
  // begin and end iterators of each containers
  // with equla and lambda the equal_strings function is much simple
  return equal(cbegin(lhs), end(lhs), cbegin(rhs), cend(rhs),
               [](char lc, char rc) { return (toupper(lc) == toupper(rc)); });
}

void test(const string &str1, const string &str2) {
  cout << str1 << " and " << str2 << " are"
       << (equal_strings(str1, str2) ? "" : " not") << " equal" << "\n";
}

void test1(const string &str1, const string &str2) {
  cout << str1 << " and " << str2 << " are"
       << (equal_strings1(str1, str2) ? "" : " not") << " equal" << "\n";
}

int main() {
  test("lambda", "Lambda");
  test("lambda", "lambada");

  test("lambda", "Lambda");
  test("lambda", "lambada");
}

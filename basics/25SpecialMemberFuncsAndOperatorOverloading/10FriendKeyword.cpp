/*
- Normally a non-member function can only access class's public members
- The class can declare a non-member function to be a "friend"
- This allows the function access to all the class's members

*/

#include <iostream>
#include <string>

using namespace std;

class Test {
  int i{42};
  string s{"Hello"};

public:
  friend void print(const Test &);
};

void print(const Test &test) { cout << "i = " << test.i << ", s = " << "\n"; }

int main() {
  Test test;
  print(test);
}

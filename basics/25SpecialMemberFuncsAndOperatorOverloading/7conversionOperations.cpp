/*
 Converts an object to some other type

 Function calls and conversion
 - When we call a function, the compiler has to find a function that resolves
   the call
   Test test;
   int x = test + 5;
   - First it tries to find an exact match
     * There is no + operator that takes a Test and int
   - Then it tries to convert the arguments
     * Test can be converted to int
     * There is a + operator that takes an int and an int
       int x = test + 5; //called as test.operator int() + 5
- This is known as implicit conversion. These are surprising and not adviced
- If you have constructor with single argument, then that will also act as an
  implicit conversion operator
- In c++11 we can turn it off by using explicit infront of the constructor
 */

#include <iostream>

using namespace std;

class Test {
  int i{42};
  string str;

public:
  operator int() const { return i; } // implicit conversion
};

class Test1 {
  int i{42};
  string str;

public:
  explicit operator int() const { return i; } // explicit conversion
};

class Test2 {
  int i{42};
  string str;

public:
  explicit operator int() const { return i; } // explicit conversion
  explicit operator bool() const {
    return i;
  } // explicit conversion operator to bool
};

// constructor with single argument
class Test3 {
  int i;

public:
  Test3(int i) : i(i) {}
};

// constructor withe explicit
class Test4 {
  int i;

public:
  explicit Test4(int i) : i(i) {}
};
int main() {
  Test test;
  cout << test << "\n";

  Test1 tes1;
  // cout << tes1 << "\n"; will not work. However it works if its conditional
  cout << static_cast<int>(test) << "\n";

  Test2 test2;
  if (test2) {
    cout << "This is allowed\n" << "\n";
  }

  // implicit conversion of constructor and create a temporary object
  Test3 test3 = 4;

  // with explicit its not allowed
  // Test4 test4;
  Test4 test4{8};
}

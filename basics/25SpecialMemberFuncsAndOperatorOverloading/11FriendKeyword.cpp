/*- We can also make an entire class as a friend
 class Test{
    friend Example;
 };

 - This gives all the member functions of Example unlimited access to Test's
   members.

 - Some C++ programmers dislike "friend" because it reduces encapsulation
 - To avoid using friend, we can create a member function which implements
   the functionality of the operator
   * This member function has direct access to all members
   * The non-member function then calls this member function

*/

#include <iostream>
#include <string>

using namespace std;

class Test {
  int i{42};
  string s{"Hello"};

public:
  friend class Example;
};

// all the member functionsof Example have access to test's private members
class Example {
public:
  void print(const Test &test) {
    cout << "i = " << test.i << ", s = " << test.s << "\n";
  }
};

// example to avoid friend
class Test1 {
  int i{42};
  string s{"Hello"};

public:
  void print() const { cout << "i = " << i << ", s = " << s << "\n"; }
};

void print(const Test1 &test) { test.print(); }

int main() {
  Test test;
  Example ex;
  ex.print(test);

  // usage of external print which calls member function
  Test1 test1;
  print(test1);
}

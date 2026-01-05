/*How output works for builtin types
- The standard library provides standalone functions which overload the
  operator << for all the built-in and library types
- This is a binary operator, so it is not a member function of ostream
   int i{1};
   cout << i;

- This is invoked as
   operator << (cout, i);
----------------------------------
Nested Calls of operator <<
----------------------------------
 - We can chain together calls of operator <<
   int i{1}, j{2};
   cout << i << j;

   * This is invoked as a pair of nested calls
      operator << (operator <<(cout, i), j);
   * The first call returns the ostream cout
   * This returned object is used as an argument to the second call
 - Because ostream cannot be copied, operator << must return a reference to the
   ostream. So its prototype must be
    ostream& operator << (ostream&, int);
 */

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

class Test {
  int i{42};
  string str{"Hello"s};

public:
  /*A member function which prints out the data members of the Test class.
   * This version will work with any output stream, not just cout. We pass the
   * output stream by reference as it will be modified inside the function*/
  void print(ostream &os) const { // has to be by reference
    os << "i = " << i << ", str = " << str << "\n";
  }
};

/*Overload operator << which prints out the data members of the Test class.
 * This calls Test class's print() method and returns the strea*/
std::ostream &operator<<(std::ostream &os, const Test &test) {
  test.print(os);
  return os;
}

int main() {
  Test test;
  test.print(cout);
  ofstream ofile("test.txt");
  if (!ofile.is_open()) {
    cout << "Could not open text.txt\n";
    return -1;
  }
  test.print(ofile);

  Test test1;
  cout << test1;
}

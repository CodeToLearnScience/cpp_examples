// specialized version of constructor
// in most cases you wouldn't need one. Compiler generated will be sufficient
// THe cases where we need to write is when class allocates memory, a thread
// object or a dabase connection.
//
//
// Example of synthesized copy constructor
/*class Test {
  int i;
  string s;

public:
  // compiler-generated copy constructor
  // initializes "this" by copying i
  // and calling std::string's copy constructor for str
  // Test(const Test& arg) : i(arg.i), s(arg.s) {}
};
*/

// To learn we will write our own String library

#include <iostream>
#include <string>

using namespace std;
using namespace std::literals;

class String {
  string s;

public:
  // constructor
  String(const string &s) : s(s) {}

  // copy constructor
  String(const String &arg) : s(arg.s) {}

  void print() { cout << s << "\n"; };
};

int main() {
  String w{"world"}; // call constructor
  String bang{w};    // call copy constructor
  String bang2 = w;  // call copy constructor

  cout << "w = ";
  w.print();
  cout << "bang = ";
  bang.print();
  cout << "bang2 = ";
  bang2.print();
}

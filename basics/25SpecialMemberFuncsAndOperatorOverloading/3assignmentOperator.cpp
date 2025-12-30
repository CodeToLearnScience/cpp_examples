// assign operator = is a member function
// automatically invoked when we do something like y = z //called as
// y.operator=(z);

// we can do multiple assignments in the same statement
//  x=y=z; => processed right to left x = (y = z)
//  After execution x and y will have same values as z
//
//  Rules for writing assignment operator are similar to copy constructor
//  In general you don't need to write one. Compiler will generate for us. And
//  again that is when the class manages resources.
//
//  Example of synthesized assignment operator
/*

   class Test{
     int i;
     string str;

     public:
      ...
      //Compiler-generated assignment operator
      //Assigns to "this" by assignment to i
      //and calling std::string's assignment operator for str
      //returns the assigned-to object by reference

       Test& operator=(const Test& arg){
         i = arg.i;
         str = arg.str;
         return *this;
       }

*/

// add assignment operator to String class
#include <iostream>
#include <string>

using namespace std;
using namespace std::literals;

class String {
  string s;

public:
  // constructors
  String() : s("") {}
  String(const string &s) : s(s) {}

  // copy constructor
  String(const String &arg) : s(arg.s) {}

  // assignment operator
  String &operator=(const String &arg) {
    s = arg.s;
    return *this;
  }
  void print() { cout << s << "\n"; };
};

int main() {
  String w{"world"};
  String bang{"bang"};
  String bang2;
  bang = w; // assign instead of copy
  bang2 = w;

  cout << "w = ";
  w.print();
  cout << "bang = ";
  bang.print();
  cout << "bang2 = ";
  bang2.print();
}

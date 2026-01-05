/*
 - Most operators can be implemented as either member functions or non-member
   functions
 - Usually they should be implemented as member functions
 - However, in some cases it is better to use non-member functions
   * Some operators cannot be be implemented as member functions
 - When to use member operators
   * Operators which change the state of the object are best implemented as
     member functions
     - Compound assignment +=, -=, *=, /=
     - increment ++, decrement --
 - Operators which are closely related to member types are best implemented as
   member functions
   * Dereference operator *
 - Some operators must be defined as member functions only
   * assignment =
   * subscript [] // takes argument as integer and will return some element from
 your object
   * function call ()
   * arrow ->
 - When to use Non-Member Operators
   * Binary operators which might require a type conversion of either argument
     should be non-member functions
     * arithmetic operators
     * equality and relational operators
     * bitwise operators
 - The input/output operator << and >>
   * These should be non-member functions for compatibility with syntax
*/

#include <iostream>
#include <string>

using namespace std;

class String {
  string s;

public:
  String(const char *str) : s(str) {}
  String(const string &s) : s(s) {}

  String operator+(const String &arg) { return s + arg.s; }

  void print() { cout << s << "\n"; }
};

class String1 {
  string s;

public:
  String1(const char *str) : s(str) {}
  String1(const string &s) : s(s) {}

  friend String1 operator+(const String1 &arg1, const String1 &arg2);

  void print() { cout << s << "\n"; }
};

// now this works with c-style string as it does conversion
String1 operator+(const String1 &arg1, const String1 &arg2) {
  return arg1.s + arg2.s;
}

int main() {

  String w{"world"};
  String bang{"!"};
  String wbang = w + bang; // calls w.operator + (bang);
  wbang.print();

  // doesn't work as + is not overloaded for c-style string
  String1 s{"world!"};
  String1 hi = "hello " + s;
  hi.print();
}

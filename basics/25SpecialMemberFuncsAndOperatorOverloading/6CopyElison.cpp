/*
 Form of optimization in which the compiler misses out calls to the copy
 constructor

example:
if we have
int x{7};
int y{x};

and if x is not used then compiler will not generate that instead compiler
does directly int y{7};

This also applies to objects
- Most modern compilers will always perform copy elison if they can even there
  is a side effect. User can disable if needed
*/

#include <iostream>

using namespace std;

class Test {
public:
  // we need to define default constructor because if we define any other
  // constructor like copy constructor, the compiler will not synthesize a
  // default constructor
  Test() { cout << "Default constructor\n"; }
  Test(const Test &other) {
    cout << "Copying\n";
  } // copy constructor with side effect as we have cout which changes the state
    // of the standard output stream
};

// copy elision happens when Function returning a temporary object
Test func() { return Test(); }

// copy elison happens when function returning a local variable
Test func1() {
  Test test;
  return test;
}

// copy elison happens when function takes argument by value
void func2(Test test) {
  // do something
}

// althoug we expect two calls (one when returning from func() and one when we
// assign) to copy constructor, the compiler has optimized away and we don't any
// copy calls but if we compile with option to disable that optimization, we
// will see the calls to copy constructor i.e., ++ -fno-elide-constructors -O2
// -std=c++11  6CopyElison.cpp
int main() {
  cout << "Calling func()" << "\n";
  Test test = func(); // how many times is "Copying" printed out?
  cout << "Returned from func() " << "\n";

  cout << "Calling func1()" << "\n";
  Test test1 = func1();
  cout << "Returned from func1() " << "\n";

  cout << "Calling func2()" << "\n";
  func2(Test());
  cout << "Returned from func2() " << "\n";
}

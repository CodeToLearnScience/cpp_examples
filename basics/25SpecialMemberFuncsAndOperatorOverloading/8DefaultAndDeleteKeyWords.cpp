/* Modern C++ allows programmers to force the compiler to synthesize special
   member functions
   * this is done by putting =default after the function parameter list
*/

/*
 - Some times its useful to prevent objects from being copied by making the copy
   constructor and assignment operator private. this was old C++ style
 - IN Modern C++, we can say that the copy constructor and the assignment
   operator are "=delete"

*/

#include <iostream>
using namespace std;

class Test {
public:
  // we need to define default constructor because if we define any other
  // constructor like copy constructor, the compiler will not synthesize a
  // default constructor
  Test() = default; // we can force compiler by using =default
  Test(const Test &other) {
    cout << "Copying\n";
  } // copy constructor with side effect as we have cout which changes the state
    // of the standard output stream
};

// prevent from copying
class Test1 {
private:
  Test1(const Test1 &);            // copy constructor is private
  Test1 &operator=(const Test1 &); // Assignment operator is private
public:
  Test1() {}
};

// prevent from copying by using delete keyword in Modern C++
class Test2 {
public:
  Test2() = default;
  Test2(const Test1 &) = delete;            // copy constructor is private
  Test2 &operator=(const Test1 &) = delete; // Assignment operator is private
};

// copy elision happens when Function returning a temporary object
Test func() { return Test(); }

int main() {
  cout << "Calling func()" << "\n";
  Test test = func();
  cout << "Returned from func()\n";

  Test1 t1, t2; // Use default constructor
  // Test t3{t1};  // Error: copy constructor is private
  // t2 = t1;      // Error: assignment operator is private

  Test2 t3, t4; // Default constructor with =default use
  // Test2 t5{t1}; //Error: use of deleted function
  // t2=t1; //Error: use of deleted function
}

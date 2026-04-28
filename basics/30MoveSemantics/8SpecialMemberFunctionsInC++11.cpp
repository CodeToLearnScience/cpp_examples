/*
------------------------
Move Operators
------------------------
- C++11 has two new special member functions: Move constructor and move
assignment operator
- Move assignment operator
- Optimized version of copy constructor and assignment operator
- They move their argument instead of copying it
- Automatically called when the argument is a moveable rvalue

----------------------------------------
Synthesized move operators
----------------------------------------
- The compiler will only synthesize a move operator if
  * The class does not define a copy constructor, assignment operator or
    destructor
  * Every data member of the class is either:
    - Built-in type
    - User-defined type with move operators
    - Static data member (not moved)
- The Synthesized move constructor will call the move constructor for each
member of the class, and the same for the move assignment operator

------------------------------------
Synthesized copy operators in C++11
------------------------------------
- If a class defines a move operator, both the copy operators will be
Synthesized ad "deleted"
- The class should define its own copy operators if it needs them
- Otherwise, the class will be move-only
- So the easiest way to create a move only class is to implement the move
operators and not the copy operators

-----------------------
Rule of Five
-----------------------
- We have talked about the rule of three for when you need to implement special
member functions. And with these two new special member functions, we now have
the rule of five in C++11
- In C++11, the Rule of Three becomes the "Rule of Five"
- If a class needs to implement a destructor to function correctly, then it
probably needs to implement the copy and move operators as well
- e.g. a class which allocates memory with "new" in its constructor
  * Destructor to call "delete" when objects are destroyed
  * Copy constructor to perform a deep copy when copying
  * assignment operator to perform a deep copy on assignment
  * Move operators to set the argument's pointer to nullptr
*/

#include <iostream>

using namespace std;

class Test {
public:
  // Default constructor
  Test() = default;

  /*
    In effect, the copy operators are declared as deleted
    // Copy constructor
    Test(const Test& other) = delete;

    //Copy assignment operator
    Test& operator=(const Test& other) = delete;
   */

  // Move constructor
  Test(Test &&other) noexcept { cout << "Move constructor called\n"; }
  // Move assignment constructor
  Test &operator=(Test &&other) noexcept {
    cout << "Move assignment operator called\n";
    return *this;
  }
};

int main() {
  Test test;                   // OK - uses default constructor
  Test test2(std::move(test)); // OK - uses move constructor
  test2 = std::move(test);     // OK - uses move assignment operator
  // Test test4(test);                             // Error! - Use of deleted
  // function
}

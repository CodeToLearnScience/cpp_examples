/*
----------------------------------------
Using Special Member Functions in C++11
----------------------------------------

----------------------------------------
When to write special Member Functions?
----------------------------------------
- The complete set of rules for the interaction between user-defined and
compiler-declared is rather complex
- Here is the table which which was drawn up by the man who implemented move
semantics (Howard Hinnant)

----------------------+--------------+--------------+---------------+---------------+---------------+--------------
User declares ↓       | default ctor | destructor   | copy ctor     | copy
assign   | move ctor     | move assign
----------------------+--------------+--------------+---------------+---------------+---------------+--------------
Nothing               | defaulted    | defaulted    | defaulted     | defaulted
| defaulted     | defaulted
----------------------+--------------+--------------+---------------+---------------+---------------+--------------
Any constructor       | not declared | defaulted    | defaulted     | defaulted
| defaulted     | defaulted
----------------------+--------------+--------------+---------------+---------------+---------------+--------------
default constructor   | user declared| defaulted    | defaulted     | defaulted
| defaulted     | defaulted
----------------------+--------------+--------------+---------------+---------------+---------------+--------------
destructor            | defaulted    | user declared| defaulted     | defaulted
| not declared  | not declared
----------------------+--------------+--------------+---------------+---------------+---------------+--------------
copy constructor      | not declared | defaulted    | user declared | defaulted
| not declared  | not declared
----------------------+--------------+--------------+---------------+---------------+---------------+--------------
copy assignment       | defaulted    | defaulted    | defaulted     | user
declared | not declared  | not declared
----------------------+--------------+--------------+---------------+---------------+---------------+--------------
move constructor      | not declared | defaulted    | deleted       | deleted |
user declared | not declared
----------------------+--------------+--------------+---------------+---------------+---------------+--------------
move assignment       | defaulted    | defaulted    | deleted       | deleted |
not declared  | user declared
----------------------+--------------+--------------+---------------+---------------+---------------+--------------

--------------------------
Rule of Zero
--------------------------
- If a class does not need to declare a destructor, it does not need to declare
copy or move operators either
- For most classes, the "Rule of Zero" is sufficient
  * Do not declare any special member functions
  * The compiler-synthesized defaults will be sufficient
- The compiler will also synthesize a default constructor
- The compiler will also synthesize default constructor
  * Unless we declare one ourselves
  * Sometimes useful to declare default constructor which initializes the
members with sensible values

-------------------------------
Rule of Three/Five
-------------------------------
- If we need a destructor, e.g. to release memory, the compiler generated copy
operators will not be correct
- In this case, we need to provide our own
  * destructor
  * copy constructor
  * copy assignment operator
- We will probably need to provide a constructor as well, e.g. to allocate
memory
- For performance, we should also add move operators
  * Otherwise the copy operators will be used

----------------------------
Move-only Class
----------------------------
- Sometimes we need to declare a destructor, but we don not want to copy the
object
  * e.g. a class which manages a network connection
  * The destructor closes the connection
  * We do not want to create a duplicate of the connection
- In the case, make the class move-only
- To make a class move-only, provide our own
  * destructor
  * Move constructor
  * Move assignment operator
  * And in that case, the compiler will synthesize the copy operators as deleted
- We will probably need to provide a constructor as well, e.g. to open the
connection
  * It maybe useful to declare a default constructor which initializes an
    unconnected object
- The compiler will synthesize the copy operators as deleted
  * For clarity, we can explicitly declare the copy operators as =delete

--------------------------
Immovable Class
--------------------------
- We can make a class which is Immovable and uncopyable
  * Objects of this class cannot be passed to a function
  * Objects of this class cannot be returned by a function
  * e.g. low level concurrency objects which release a lock at the end of their
    scope. These are objects which will lock a mutex when they are created, and
    then they unlock the mutex when they are destroyed. These are designed to be
    used within a single scope. So the idea is, when the program goes out of
    scope, the mutex is automatically unlocked. So the designers of the
    Concurrency Library have enforced this scope lifetime, by making it
    impossible to pass these to functions or return them from functions
- To make a class object immovable, delete the copy operators
  * The compiler will not synthesize the move operators
  * Any copy or move operation will invoke the copy operators, which are deleted
    and we will get a compiler error

-------------------------
Copy-only class
-------------------------
- We can make a class which can be copied, but not moved
- To do this, we declare the move operators as deleted

  Test(Test&& other) noexcept = delete;         //Move constructor
  Test& operator=(Test&& other)noexcept=delete; //Move assignment operator

- Even though an operator is deleted, the compiler can still choose it as the
best match
- This can have surprising results

   Test test;                     //OK - uses the default constructor
   Test test2(std::move(test));   //Does not fall back to copy constructor

- For this reason, copy-only classes are not recommended
    */

#include <iostream>

class Test {
public:
  // Default constructor
  Test() = default;

  // The copy operators are declared as deleted
  // Copy constructor
  Test(const Test &other) = delete;

  // Copy assignment operator
  Test &operator=(const Test &other) = delete;

  /*
   // The compiler does not generate any move operators
   */
};

namespace copy_only_class {
class Test {
public:
  // Default constructor
  Test() = default;

  // The copy operators are declared as deleted
  // Copy constructor
  Test(const Test &other) { std::cout << "Copy constructor called\n"; }

  // Copy assignment operator
  Test &operator=(const Test &other) {
    std::cout << "Copy assignment operator called\n";
    return *this;
  }

  // The move operators are declared as deleted
  Test(Test &&other) noexcept = delete;

  // Move assignment operator
  Test &operator=(Test &&other) noexcept = delete;
};

void example() {
  Test test; // OK - uses default constructor
  // Test test2(std::move(test)); // Does not fall back to copy constructor
  Test test3(test); // OK - uses copy constructor
}
} // namespace copy_only_class

int main() {
  Test test; // OK - uses default constructor
  // Test test2(std::move(test));   //Error! Use of deleted function
  // Test test3(test);              //Error! Use of delted constructor

  std::cout
      << "===============copy-only class example=======================\n";
  copy_only_class::example();
}

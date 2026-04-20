/*
----------------------------------
Move-Only Types and RAII
----------------------------------
----------------
Move-only class
----------------
- In C++, you can create Move-only type. This is something which can be moved
but not copied.
- To make move-only class, implement the move operators and make the copy
operators deleted

  class Test {
  public:
    Test(const Test &) = delete;             //delete copy constructor
    Test &operator=(const Test &) = default; //delete copy assignment operator
    Test(Test &&) noexcept;                  // implement move constructor
    Test &operator=(Test &&) = default;      // implement move assignment
                                             // opeator
    ...                                      // other member functions
  };

-------------------------------
Move-Only types
-------------------------------
- C++ has some types which cannot be copied, but can be moved
  * fstream, iostream
  * (classes used in multithreading)
  * ("Smart pointer" class)
- These types follow the RAII idiom
  * Only one object can own a given resource instance at a time
  * The object acquires ownership of the resource in the constructor
  * The object releases ownership of the resource in the destructor
- The ownership of the resource can be transferred from one object to another
using move semantics

--------------------
fstream
--------------------
- fstream has a file handle as a data member. This is something that is used by
the OS to communicate with the file on disk
- The fstream constructor opens the file. It will be given a handle by the OS
- The fstream destructor closes the file. So it will return the handle back to
OS
- An fstream object cannot be copied, but it can be moved, because that would
mean there are two objects which are both goint to try to close the file, which
is not desirable.
  * Moving will cause the file handle to be transferred, from one object to
    another
  * The moved-from object no longer owns the file handle. It now has a null
    handle or invalid file
  * The object which is moved into becomes the owner of the file handle, and it
    is responsible for releasing the file handle when the file is no longer
    needed. So when the destructor is called for that object, it will close the
    file unless of course if the file handle has been moved into another object
    in the meantime.

--------------------------------------------
Lambda capture and move-only objects
--------------------------------------------
- There is one issue with move-only objects in C++11, which comes into effect if
we try to use them in the Lambda expressions.
- C++11 Lambda expressions are not good at capturing move-only objects

   fstream fs("output.txt");

   //what syntax do we use to capture fs?
   [fs]      //capture by value - does not compile
   [&fs]     //capture by reference - no transfer of ownership
   [???]     //capture by move - not supported in C++11
- capturing by reference give us access to the file, but it does not give us the
ownership
- If we want to be able to transfer ownership into the Lambda expression, then
we need a capture by move and that is not supported in C++11

--------------------------
Capture by move
--------------------------
- C++14 has "generalized" lambda capture. Which means we can create lambda-local
variable
- A variable in the outer scope can be moved into a lambda-local variable

  fstream fs("output.txt");
  [lfs = std::move(fs)] //now owned by lambda body's local variable lfs. This
                        //"lfs" variable is going to be local variable to the
                        //lambda expression body
- This allows capture by move
  * lfs is deduced as fstream. That is they type of this variable "lfs" will be
    deduced from its initializer. If we make this initializer an rvalue, then
    this is going to be initialized using the move constructor as shown above.
    This will move the file handle from this "fs" object in scope, into the
    local variable in the lambda expression. That is how you do capture by move
  * The move constructor is called to initialize lfs from the file stream
    argument from the outer scope variable "lfs" and this variable in the lambda
    expression will take ownership of the file handle.
 - This was the 2nd most requested feature in C++14!
    */

#include <iostream>
#include <vector>

using namespace std;

namespace move_only_type {
class MyClass {};

class Test {
private:
  int i{0};
  MyClass m;

public:
  Test() = default;
  /*when we delete these functions, it does not mean that the functions are non
   * existent! It means that the compiler can decide that these are the best
   * match. But when they actually get called, there is a compiler error. So
   * these are functions which exist and do not exist at the same time. They are
   * "Schroedinger's cat" functions, if you like.*/
  Test(const Test &) = delete;            // delete copy constructor
  Test &operator=(const Test &) = delete; // delete copy assignment operator

  // implement move constructor
  Test(Test &&arg) noexcept : i(arg.i), m(std::move(arg.m)) {
    cout << "Move constructor called\n";
  }

  // implement move assignment operator
  Test &operator=(Test &&arg) noexcept {
    cout << "Move assignment operator called\n";
    if (this != &arg) {
      i = arg.i;
      m = std::move(arg.m); // force move assignment operator to be called
    }
    return *this;
  }
};

void example() {

  Test test; // call default constructor
  // cout << "Copying: ";
  // Test test2 = test; // call copy constructor

  /*when we call this, we may not get "Move constructor called" as this statment
   * being optimzed out by compiler */
  cout << "\nMoving temporary: ";
  Test test3 = Test(); // call move constructor by using temporary object
  cout << "\nMoving value: ";
  Test test4(std::move(test)); // call move constructor by casting to rvalue

  cout << "\n";

  // Test test5;
  // cout << "\nAssigning: ";
  // test5 = test;  // call copy assignment operator

  Test test6;
  cout << "\nAssigning from temporary: ";
  test6 = Test(); // call move assignment operator
}

void lambda_example() {
  Test test;
  /*[test]() {
    cout << "Lambda capturing by value\n";
  };*/ // doesn't compile because we tried to call the copy constructor, which is
     // deleted
}

void move_by_capture_example() {
  vector<string> strings(5);

  cout << "======================================================\n";

  cout << "Capture by reference\n";
  [&strings]() { cout << "Size in  lambda = " << strings.size() << "\n"; }();
  cout << "After calling lambda, size in main = " << strings.size() << "\n";

  cout << "\n" << "Capture by move\n";
  [vs = std::move(strings)]() {
    cout << "size in lambda = " << vs.size() << "\n";
  }();
  cout << "After calling lambda, size in main = " << strings.size() << "\n";
}
} // namespace move_only_type

int main() {
  move_only_type::example();
  move_only_type::move_by_capture_example();
}

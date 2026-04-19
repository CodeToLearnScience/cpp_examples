/*
-----------------------
Move Operators
-----------------------
---------------------------------
Rvalue references and overloading
---------------------------------
- We can overload a function so that it behaves differently depending on whether
its argument is moved

  void func(const myclass& obj); //called when we pass an lvalue
  void func(myclass&& obj);      //called when we pass an rvalue

- Two of the most useful functions to overload this way are the copy constructor
and assignment operator.
  * In our previous examples, with a vector of 1million strings, the copy
    constructor is going to call the copy constructor for every one of those
    strings
  * These member functions typically copy all the members of the class. Often
    they create a new copy of a resource
  * Moving instead of copying improves performance

---------------------------
Move Operators
---------------------------
- C++11 added a new special member functions for this purpose
  * Move constructor
  * Move assignment operator
- These are called automatically if the passed object is a moveable rvalue
- These are overloads of the copy constructor and assignment operator which take
rvalue references.
- The assignment operator is now called the "copy assignment operator"
  * To avoid the confusion with the move assignment operator

-------------------------
Move operator syntax
-------------------------

   Test(const Test& arg);                //copy constructor
   Test(Test&& arg) noexcept;            //Move constructor

   Test& operator = (const Test& arg);   //Copy assignment operator
   Test& operator = (Test&& arg);        //Move assignment operator

- The move operator argument cannot be const. That is because we are going to
move from the argument. So we are going to modify it, so it cannot be const
- The move operators should not throw exceptions
  * The first one is that generally move operators should just "move" data
    around. They should not allocate new resources or do other things, which
    could throw exceptions
  * The second one is, if you are halfway through a move operation, so you have
    some data in one object, and the rest of the data in another object. If an
    exceptions is thrown, there is no simple way to recover from a
    part-completed move
  * And third reason is, if you want to put objects of your class inside one of
   the library containers (STL container), STL containers will only call an
   element's move operator if it is noexcept. Otherwise code will not compile
- The move assignment operator returns the assigned-to object by lvalue
references and that will allow you to assign it again.

-------------------------------
Move Operator Implementation
-------------------------------
- We will add move operators to this class

  class Test{
     private:
       int i{0};    //built-in member
       MyClass m;   //class member

     public:
       Test() = default; //constructor (call m's constructor)
  };
- So what does it mean to move an object of this class?
  * We need to move the int member i, and the object member m. So if we are
    calling the move constructor, we need to call the move constructor of these
    members, i.e., for built-in members, we just copy them. For class members,
    we call the corresponding move operator

----------------------------------------------------
Move Operators for Derived Classes
----------------------------------------------------
- When writing a move opertor for a derived class, we should call the
corresponding operator for the base class
- To do this, we must pass the argument as an rvalue

  //copy constructor
  Derived(const Derived& arg); Base(arg) {...}

  //Move constructor
  Derived(Derived&& arg) : Base(std::move(arg)) noexcept {...}

- In above for the move constructor, we need to make sure that the base class
move constructor gets called. So we need to provide an rvalue. The argument to
the move constructor is actually an lvaue (it has a name and we could take its
address), so we need to call move(), to cast it to an rvalue and that will call
the move constructor of the base class

-----------------------------------------------
Compatibility with older versions of C++
-----------------------------------------------
- Classes written before move semantics will behave the same way when compiled
with Modern C++ compiler as they did before
- If we copy an rvalue object which does not have a move constructor, the copy
constructor will be called instead
- If we assign an rvalue object which does not have a move assignment operator,
the copy assignment operator will be called instead
*/

#include <iostream>

using namespace std;

class MyClass {};

// class with the move constructor
class Test {
private:
  int i{0};
  MyClass m;

public:
  Test() = default;

  // copy constructor
  Test(const Test &arg) : i(arg.i), m(arg.m) {
    cout << "Copy constructor called\n";
  }

  // Move constructor
  Test(Test &&arg) : i(arg.i), m(std::move(arg.m)) {
    cout << "Move constructor called\n";
  }

  // Copy assignment operator
  Test &operator=(const Test &arg) {
    cout << "Copy assignment operator called\n";
    if (this != &arg) {
      i = arg.i;
      m = arg.m;
    }
    return *this;
  }

  // Move assignment operator
  Test &operator=(Test &&arg) noexcept {
    cout << "Move assignment operator called\n";
    if (this != &arg) {
      i = arg.i;
      m = std::move(arg.m); // force move assignment operator to be called
    }
    return *this;
  }
};

int main() {

  Test test; // call default constructor
  cout << "Copying: ";
  Test test2 = test; // call copy constructor
  cout << "\nMoving temporary: ";
  Test test3 = Test(); // call move constructor by using temporary object
  cout << "\nMoving rvalue ref: ";
  Test test4(std::move(test)); // Call move constructor by casting test to
                               // rvalue

  cout << "\n";

  Test test5;
  cout << "\nAssigning: ";
  test5 = test2; // call copy assignment operator

  Test test6;
  cout << "\nAssigning from temporary: ";
  test6 = Test(); // call move assignment operator
}

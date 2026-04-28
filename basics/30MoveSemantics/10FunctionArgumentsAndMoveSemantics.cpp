/*
----------------------------------------------------
Function Arguments and Move Semantics
----------------------------------------------------
- We are going to try and find the fastest way of passing an object to a
Function in C++11
- There are quite a few ways of passing objects, so let's make sure we fully
understand

- Pass by value
  * Copy constructor called
  * Function has its own copy of the caller's object
  * Caller's object is unmodified

- Pass by const reference
  * Function has read-only access to caller's object
  * Caller's object may be unmodified

- Pass by non-const reference and pass by address
  * Function has full access to caller's object
  * Caller's object maybe modified

- Pass by move
  * Move constructor called
  * Function now owns the caller object's data
  * Caller's object is unusable (until re-assigned)

----------------------
Older C++ Advice
----------------------
- When passing an object to a function which will not modify it, the most
efficient way is to:
  * Pass built-in types and small objects by value
  * Pass larger objects by const reference
- Does this still apply in C++11?
  * Best way to approach this is by looking at constructors

-------------------------
constructor Argument
-------------------------
- We want to initialize the std::string member of this class using both lvalues
and rvalues
- What is the most efficient way to do this?

  class Test{
    string m_str;

  public:
    Test( ??? ){...} //Takes a string argument which initializes the str member
                     //Other public member functions
  };
- Let's go thorugh the possibilites of ??? (how do pass) as follows

---------------------------------
Pas by const Reference
---------------------------------
- The argument is bound to the passed object
- The argument is copied into the data member

   Test::Test(const string& str) : m_str(str){}

   string name;
   Test ltest(name); //Lvalue passed - str binds to name
                     //str is copied into m_str

   Test rtest(std::move(name)); //Rvalue passed - str binds to name
                                //str is copied into m_str

- In both cases, the passed object will be bound to this reference, or rather,
the reference is bound to the object. In the first case, the argument "str" is
going to be a reference to the caller's object. When we use that to initialize
the data member of the class (m_str(str)), its going to be by copying because
it's a value member. So we have just one copy operation, where the argument is
copied into the data member. There is no copy for the actual argument, because
these are bound by reference to the passed object. This is true for both cases

--------------------------
Pass by Value/Pass by Move
--------------------------
- Lvalues are passed by value
  * str is a copy of the passed object
  * Two copy operations if we have an lvalue argument
- Rvalues are passed by move
  * The passed object is moved into str
  * That's one move operation and one copy operation

     Test::Test(string str) : m_str(str){}

     string name;
     Test ltest(name); //Lvalue pased - name is copied into str
                       //str is copied into m_str

     Test rtest(std::move(name)); //Rvalue passed - name is moved into str
                                  //str is copied into m_str

-----------------------------
Pass by Rvalue reference
--------------------------
- Lvalues cannot be bound to an rvalue reference
- Rvalues are passed by move
  * The passed object is moved into str
- If the passed object is an lvalue, then you are not allowed to do that

    Test::Test(string&& str) : m_str(std::move(str)){}

    str name;
    Test ltest(name);  //compiler error

    Test rtest(std::move(name));  //Rvalue passed - str binds to name
                                  //str is moved into m_str

------------------
Relative Costs
------------------
- Pass by const reference
  * Lvalue object passed - 1 copy
  * Rvalue object passed - 1 copy
- Pass by value/pass by move
  * Lvalue object passed - 2 copied
  * Rvalue object passed - 1 move + 1 copy
- pass by value then move
  * Lvalue object passed - 1 copy + 1 move
  * Rvalue object passed - 2 moves
- Pass by rvalue reference
  * Lvalue object passed - not allowed
  * Rvalue obhect passed - 1 move

- Usually moves are much quicker for copies, but it is not allowed at all for
lvaues. So that is not the answer, or at least not the complete answer. For an
lvalue the pass by const reference is the winner. So we can one for lvalue and
one for rvalue. Will that work? Yes as shown below

-------------------------
constructor argument
-------------------------
- The most efficient way to write the constructors for this class is to:
  * Pass lvalue by const reference
  * Pass rvalue by rvalue reference

  class Test{
    string m_str;

  public:
    Test(const string& str) : m_str(str){}        //called when rvalue passed
    Test(string&& str) :m_str(std::move(str){}    //called when rvalue passed
  };
- However, this requires writing two identical functions. But C++11 does
actually provide a way around that.
  */

#include <iostream>
#include <string>

using namespace std;

class Test {
  string m_str;

public:
  /* If we are very cunning, we could look at this string argument and we could
   * say this is actually a copy of the caller's object, so we can do what we
   * like with this. So if we move from it, it is not going to cause the caller
   * ant problems. So we could actually move into the data member of the class*/
  Test(string str) : m_str(std::move(str)) {}
};

int main() {

  string name;
  // so if we have an lvalue, this will be copied into the argument, and then
  // this copy can be moved into the data member
  Test ltest(name); // lvalue passed - name is copied into str
                    // str is passed into m_str

  // if we have an rvalue object passed, that can be moved into the argument,
  // and then the argument can be moved into the member. So that's two move
  // operations
  Test rtest(std::move(name)); // rvalue passed - name is moved into str
                               // str is moved into m_str
}

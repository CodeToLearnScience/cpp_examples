/*
--------------------------
Lvalue and Rvalue
--------------------------
- In C++ every object is either be an lvalue or an rvalue
- Originally, an lvalue could appear on the left of an assignment
- An rvalue could only appear on the right
   x = 2;      //x is an lvalue, 2 is an rvalue
   x = func(); //x is an lvalue, return value from func() is an rvalue

-----------------------------
lvalue and rvalue in C++
-----------------------------
- Unfortunately the above simple rule is not sufficient for C++
- In C++ we have overloaded operators and some operators can return things which
can be assigned to so we need a different rule.
- In C++, an lvalue represents a named memory location
  * A variable must have a name
  * We can take its address using the & operator
  * x is an lvalue //name is x &x is legal
- Anything else is an rvalue
  * 2 is an rvalue      // 2 has no name, &2 is not legal
  * func() is an rvalue //return value from function call has no name
                        // &func() is not legal
- The reason why it is important is lvalues and rvalues can behave differently
when passed as function arguments

-------------------
Pass by value
-------------------
- lvalues can be passed by value

  void func(int); //function taking int by value

  int x=2;     //x is an lvalue
  func(x);     //the value of x is copied into the function argument - OK

- rvalues can also be passed by value

   func(2); //2 is copied into the function argument - OK

--------------------
Pass by address
--------------------
- However, if we pass by address, it does make a difference
- lvalues can be passed by address

   void func(int *);  // function taking int by address

   int x = 2;         // x is an lvalue
   func(&x);          // x is passed by address - OK

- rvalues cannot be passed by address

   func(&2);          // 2 cannot be passed by address - Error!

---------------------
Passign by reference
---------------------
- This is really another way of taking the address. So again we have the same
rule
- lvalues can be passed by reference. That is a non-const reference. But we
cannot pass rvalues by non-const reference

  void func(int&);        //function taking int by reference
  int x = 2;              //x is an lvalue
  func(x);                //x is passed by reference - OK

- rvalues cannot be passed by reference
  func(2); // 2 cannot be passed by reference - Error!

----------------------------------
Passing rvalue by const reference
----------------------------------
- In general, pass by address and pass by non-const reference are used when the
function wants to modify the argument
- This makes no sense for rvalues, so it is not allowed
- However, if we are passing by const reference, which is used as a more
efficient way of passing large objects by value, then that is sort-of like
passing by value so we have the same rules as for pass by value.
- Therefore, passing rvalues by const reference is allowed

  int get() {return 2; } //function returning an int

  void func(const int&); //Function taking int by const reference
  func(get());           //Return value from get() is an rvalue
                         //The rvalue is passed by const reference

--------------------
Pass by move
--------------------
- In older C++, an argument is always copied by default

  void func(Type obj); //func makes its own copy of obj. So the function
                       //has a local variable, which is a copy of the argumet
                       //that was passed to it.

- In C++11, we have pass by move, the argument can be moved into the function.
So the variable in the function actually has the data that used to be in the
object which was passed to the function
  * This actually uses the same syntax as passing by value
  * object is an rvalue
  * and Type is "movable"
  * True for all C++ library types (except for ...). Most of the exceptions are
    to do with thread synchronization
- on the other hand, if the object which is passed is an lvalue, obj will be
copied if
  * obj is an lvalue
  * or Type is not moveable (includes built-in types)
  * So if you have some classes and they were not written for move semantics and
    you pass them by value. This provides compatability with old code
*/

#include <cstdio>
#include <iostream>

int get() { return 2; } // function returning an int

void print_get(const int &x) { // function taking int by const reference
  std::cout << "hello " << x << "\n";
}

int main() {
  print_get(get()); // return value from get() is an rvalue
                    // the rvalue is passed by const reference
                    // So you can actually pass an rvalue by reference to const
                    // as well as by value
}

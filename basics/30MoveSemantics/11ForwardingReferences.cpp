/*
----------------------------------
Forwarding References
----------------------------------
---------------------------
Nested Reference
---------------------------
- Programmers cannot directly create a nested Reference because the syntax does
not exist. So compiler will not let us.

   int &&x = y; //Error

- However, the compiler can do this internally for a type alias or a template
parameter
- We have type alias, for a reference to int. So whenever we put "int_ref"
the compiler will replace this by reference to int
   using int_ref = int&; //or typedef int& int_ref;

   int i{42};
   int_ref j{i};     //j is a Reference to int
   int_ref& rj{j};   //rj is a Reference to (Reference to int)

- With int_ref& rj{j}; the compiler will perform something called "reference
collapsing". So these multiple reference will be collpased into a single
reference
- The type of the result is determined by "reference collapsing"
- The reference to (reference to int) "collpase" into reference to int

------------------------------------
Reference Collapsing Rules
------------------------------------
- rvalue reference can also appear in nested reference
- The result is an rvalue reference only if they are both rvalue reference

  using lval_ref = int&;
  using rval_ref = int&&;

  lval_ref& => int&;
  lval_ref&& => int&; //rvalue reference to lvalue reference
  rval_ref& =>int&;
  rval_ref&& => int&&;

- These reference collpases are basically "an" and operation.
- If we have an rvalue reference to something which is an rvalue reference, then
that collpases down into an rvalue reference. If we an lvalue reference anywhere
then that collpases down to an lvalue reference.

----------------------------
&& Argument Parameters
----------------------------
- So far, the && argument has always been a specific type

  func(Test&& x);

  * The type of the parameter x is rvalue reference to Test
  * It can only be bound to an rvalue (xvalue or prvalue)

-------------------------------
&& Template Argument Parameters
-------------------------------
- && has completely different effects if the argument is generic

  template <typename T>
  func(T&& x);

  * x is now a "Forwarding" reference or sometimes a universal reference
  * It is called universal because it can can be bound to an rvalue or an lvalue

- When the compiler instantiates this function, how does it deduce the argument
type?

------------------------------------------
Template Argument Deduction
------------------------------------------
- When deducing the argument type for a forwarding reference, the compiler first
examines the value category


  template <typename T>
  func(T&& x);

If an lvalue is passed to func(), T is deduced as lvalue reference to Test
  * Reference collapsing is then applied
  * Example: T is Test& and x is T&& => Test&
- If an rvalue is passed to func(), the orginal type is deduced for T
  * Example: T is Test and x is T&& => Test&&

---------------------------------------
Why Are Forwarding References Useful?
---------------------------------------
- We found that the most efficient way to implement a constructor is to write
two separate functions

  Test(const Test& obj);
  Test(Test&& obj); //Apart from the argument type, these are identical

- Now if we have many parameters or even a variable number...
  * Two functions is a bit of nuisance, but maybe you can live without that. But
    for example you have four arguments, and everyone of them can be either an
    lvalue or an rvalue so that's 20 different overloads that you'd have to
    write with all exactly the same function bodies, but different arguments
- With forwarding references, we only need to write the function once

  func(T&&); //the compiler will instantiate overloads as needed

- If you can get the compiler to do the work for you, instead of having to write
the code yourself, that is always a good thing. And that is actually a direction
that C++ is going in.
*/

#include <iostream>

using namespace std;

namespace nested_reference {

void func(int &x) { cout << "func called with argument int& \n"; }

void example() {
  int i{42};
  // int& & ri = i; //Error;
  using int_ref = int &; // or typedef int& in_ref;
  int_ref j{i};          // j is a reference to int
  int_ref &rj{j};        // rj is a reference to (reference to int)
  func(rj);
}

} // namespace nested_reference

namespace argument_deduction {
class Test {};

template <class T> void func(T &&x) { cout << "func called\n"; }

void example() {
  Test t;
  Test &rt{t};

  /* The template parameter type will be lvalue reference to Test and then x
   * will be an rvalue reference. The rvalue reference to lvalue reference will
   * collpase down to lvalue reference to Test */
  // T is Test& and x is T&& => Test&
  func(t); // compiler instantiates func(Test& x)

  // T is Test& and x is T&& => Test&
  func(rt); // compiler instantiates func(Test& x)

  /* If we pass an rvalue object, then the template parameter is a Test, not a
   * reference, just a Test. And x will be an rvalue reference to that. So that
   * is rvalue reference to Test. So if we pass an rvalue object, then there is
   * no reference collapsing. The compiler will instantiate a function which
   * takes an rvalue reference to Test as its argument */
  // T is Test and x is T&& => Test&&
  func(std::move(t)); // compiler instantiates func(Test&& x)
}

} // namespace argument_deduction

int main() { nested_reference::example(); }

/*
--------------------------
Perfect Forwarding
--------------------------
-----------------
Forwarding
-----------------
- A function that passes some or all of its arguments to another function is
said to "forward" them

  void f(Test x){
    g(x); // f() forwards the argument x to g()
  }

- With "perfect forwarding", the properties of the passed object(s) are
preserved
  * If x is modifiable in f(), it is modifiable in g()
  * If x is unmodifiable in f(), it is unmodifiable in g()
  * If x was moved into f()'s argument, it will be moved into g()'s argument

---------------------------------------
Applications of Perfect Forwarding
---------------------------------------
- Perfect forwarding is used to write functions which call constructors
  e.g. make_pair() from standard library
- If a passed object is an rvalue, the more efficient move constructor will
automatically be called
- Perfect forwarding is also used by variadic templates to dispatch their
arguments to functions which process them
  * Retains the information whether the passed object was an lvalue or an rvalue

---------------------------------
Forwarding Functions
---------------------------------
- We have three overloads of g()

  void g(Test& x);              //x is modifiable in g()
  void g(const Test& x);        //x is not modifiable in g()
  void g(Test&& x);             //x is moved into g()

- ...and three overloads of f() which forward to them

  void f(Test& x) {g(x);}             //f() calls unmodifiable version of g()
  void f(const Test& x) {g(x);}       //f() calls unmodifiable version of g()
  voif f(Test&& x) {g(std::move(x));} //f() moves x into g()

- Can we write f() as a template function with a forwarding reference?

-----------------------------------
move() problem
-----------------------------------
- The rvalue version of f() does not call the rvalue version of g()
  * It calls the lvalue version of g()
- The problem is that inside f(), x is an lvalue

  void f(Test&& x){ //rvalue instantiation of f()
                    //x has a name and an address - it is an lvalue
    g(x);           //lvalue argument - calls g(Test&);
  }
- To call the move version of g(), we need to convert it to an rvalue

  void f(Test&& x){  //rvalue instantiation of f()
    g(std::move(x)); //rvalue argument - calls g(Test&&);
  }

-------------------------------
Conditional std::move() needed
-------------------------------
- However, std::moe() always casts its argument to an rvalue
  void f(Test& x){ //lvalue instantiation of f()
    g(std::move(x));               //rvalue argument - calls g(Test&&);
  }
- The move is also called when x is an lvalue reference!
- We need some way to avoid performing the cast in this case. And in fact, the
library provides something which does this

--------------------------
std::forwad()
--------------------------
- std::forward() casts its argument to rvalue reference

   std::forward<T>(x); //equivalent to static_cast<T&&>(x). It works because of
                       //reference collapsing
- Reference collapsing provides the desired behaviour
  * If x is of type T&, it will be left as an lvalue reference to T
  * If x of type T or T&&, it will be cast to an rvalue reference to T
- std::forward() does not cast its argument if it is an lvalue reference
- NB std::forward<T> requires a parameter, while std::move does not

-------------------------------------------------------
- This may all seem a bit elaborate. And if you only write applications, then
you may never actually need to use this. But it is a useful technique if you
are writing library code, because it is a template so you do not need to
actually write very much code, and it will automatically perform move operations
if they are available and that is always the most efficient form.
*/

#include <iostream>

using namespace std;

namespace forwarding_ref {
class Test {};

void g(Test &x) { cout << "Modifiable version of g called\n"; }
void g(const Test &x) { cout << "Immutable version of g called\n"; }
void g(Test &&x) { cout << "Move version of g called\n"; }

// template <class T> void f(T &&x) { g(x); }
// template <class T> void f(T &&x) { g(std::move(x)); }
template <class T> void f(T &&x) { g(std::forward<T>(x)); }

void example() {
  Test x;
  const Test cx;
  cout << "Calling f() with lvalue argument\n";
  // If we pass an lvalue object, then T will be deduced as an lvalue reference
  // to Test. Then we have reference collapsing, and this will instantiate a
  // function which takes lvalue reference. When we pass x to g(), that is going
  // to call the version which takes lvalue reference to Test.
  f(x);
  // if we pass a const lvalue to this function, T will be deduced as const
  // lvalue reference
  cout << "\nCalling f() with const lvalue argument\n";
  f(cx);
  // if we pass an rvalue, then the compiler will instantiate this with an
  // rvalue reference argument
  cout << "\nCalling f() with rvalue argument\n";
  f(std::move(x));
}
} // namespace forwarding_ref

int main() { forwarding_ref::example(); }

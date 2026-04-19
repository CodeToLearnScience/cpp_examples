/*
--------------------
Lvalue reference
--------------------
- A reference to an lvalue is typically implemented as a pointer
- The compiler adds code to dereference the pointer as needed

  int x;
  int& y = x; //Equivalent to int *y = &x;
  y = 3;      //Equivalent to *y=3;

- This requires that x has a name and an address
  * i.e., x must be an lvalue
- This is known as an "lvalue reference"

--------------------------
lvalue reference to rvalue
--------------------------
- We cannot bind an lvalue reference to an rvalue...
  int& x = 3; //Error
- ...unless the referenceis const
  const int& x = 3; //Ok
- The compiler will add code which makes this appear to work like a const
reference to an lvalue

------------------------
Rvalue reference
------------------------
- C++11 has the concept of an "rvalue reference". Which is not actually
reference at all. It is just a bit of syntax. The actual syntax looks bit
peculiar
- This is a syntactic device which indicates that a function argument must be a
moveable rvalue
- An rvalue reference has '&&' after the type. This is not a reference to a
reference. It is actually some special instruction to the compiler

   void func(int&& x); //func's argument is an 'rvalue reference'
   func(2);  //2 is an rvalue. OK. Literals are rvalues, and built-in types are
             //regarded as moveable even though they actually get copied
   int y{2};
   func(y);  //Error: y is an lvalue

-------------------------------------
Moving a function call argument
-------------------------------------
- A function argument can be an "rvalue reference"
- The passed object will be moved into the argument if
  * The object is an rvalue
  * and its type is moveable
- otherwise, the call does not compile
- This allows us to overload the function to behave differently depending on
whether the passed object is an lvalue or an rvalue


-------------
std::move
-------------
- If we want to pass an lvalue to a function which takes an rvalue reference, we
have to cast it to rvalue. Well this must mean that you do not actually want to
keep the data in the lvalue
- std::move() will cast its argument to rvalue. std::move doesn't move anything.
All it does is cast its argument. For example, in the case of previous example

   int y{2};
   func(std::move(y));  // y is cast to an rvalue OK

- This will move y's data into the function argument x
- This should only be done if y's data is expendable
  * After calling func(), y's data may be empty or unusable
  * If we wantt to use y again, we must re-assign its data

-----------------------
Argument Type Summary
-----------------------
- Lvalue: func(int x);
  * We can pass an lvalue
  * The function has a copy of the pased object's data
  * Or we can pass a moveable rvalue and the function now owns the pased
    object's data

- Lvalue reference: func(int& x);
  * We can pass an lvalue, but not an rvalue
  * The function can modify the passed object's data through the reference

- Const lvalue reference: func(const int& x);
  * We can pass an lvalue or an rvalue
  * The function cannot modify the passed object's data through the reference

- Rvalue reference: func(int&& x);
  * We can pass a moveable rvalue, but not an lvalue
  * The passed object will be moved into the function argument, and the function
    now owns the passed object's data
*/

#include <iostream>

using namespace std;

void func(int &&x) { // Function's argument is an "rvalue reference"
  cout << "rvalue reference example " << x << "\n";
}

namespace move_example {

void test(const string &s) { cout << "Lvalue reference version\n"; }

void test(string &&s) { cout << "Rvalue reference version\n"; }

void example() {
  string l{string{"Perm"}};
  string &lr{l};

  cout << "Temporary object: ";
  test(string{"Temp"});
  cout << "Lvalue variable: ";
  test(l);
  cout << "Lvalue reference: ";
  test(lr);
  cout << "std::move(): ";
  test(std::move(l));
  cout << "\n";

  string &&r{string{"Temp"}}; // declare this variable as an rvalue reference.
                              // You are allowed to do that
  cout << "Rvalue variable: ";
  test(r); // this actually calls Lvalue reference function. Although r is
           // declared as rvalue referene. it is actually an lvalue. Because it
           // has name, and it has an address. So we could do "&r", and that
           // would be legal
  cout << "std::move(): ";
  test(std::move(r));
}

} // namespace move_example

int main() {
  func(2);
  int y{2};
  // func(y); // Error: y is an lvalue
  move_example::example();
}

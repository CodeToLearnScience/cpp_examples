/*
------------------------------
decltype
------------------------------
- Consider unique_ptr with a custom deleter
  - We wanted a template parameter to have the same type as a lambda expression
  - We used decltype
    decltype(end_connection)

------------------------------
    decltype
------------------------------
- The decltype keyword was added in C++11
- decltype can only be used at compile time
- decltype gives the type of its argument
- The argument must be an expression or an object
- Some compilers have a non-standard extension "typeof", which is similar
- decltype does not evaluate its argument
- It does not cause any code to be executed
- The compiler will replace decltype with the type that the argument would
   return decltype(1 + 2) y  // Declare variable y with the same type as (1+2)
- For a named variable, decltype will give the type it was declared as
   int x;
   decltype(x)   // Gives "int"

----------------------------
decltype vs auto
----------------------------
- auto makes a variable have the same type as its initializer
  auto x(6);                 // The type of x is int
- decltype gives the type of an object or an expression
  decltype(x) y;             // The type of y is int
- Unlike auto, decltype will retain const, reference, etc
  const int cx;
  auto y = cx;               // The type of y is int
  decltype(cx) cz;           // The type of cz is const int

---------------------------
# decltype with lvalues
---------------------------
- decltype with named variable
  - The result is the type that the variable was declared as
  - int x;
  - decltype(x) // Gives "int"

- decltype with lvalue expression
  - The result is an lvalue reference to the expression's deduced type
  - decltype(x + y) // Gives "int&"

- This includes variables inside paranthesis ()
  - decltype((x)) // Gives "int&"

-----------------------------
# decltype with rvalues
-----------------------------
- decltype with prvalue
  - The result is the argument's deduced type
  - decltype(2) // Gives "int"

- decltype with xvalue
  - The result is an rvalue reference to the argument's deduced type
  - decltype(Test()) // Gives "Test&&"

-----------------------
# decltype(auto)
-----------------------
- In C++14, we can use "auto" as the argument to decltype
  - decltype(auto)

- This works like auto, except it retains qualifiers
  - const int& a(99);     // The type of a is const int&
  - auto b = a;           // The type of b is int
  - decltype(auto) c = a; // The type of c is const int&

-----------------------------------
# Applications of decltype
-----------------------------------
- decltype is mainly used in compile-time programming

  // Return the sum of two arguments of any type
  template <typename T, typename U>
  auto add(T t, U u) -> decltype(t + u) {    // C++11 requires the return type
    return t + u;
  }

- It can also be used with C++14's generic lambdas
  // Return a vector of n elements, initialized to x
  auto make_vector = [](auto x, size_t n) {
    return vector<decltype(x)>(n, x);
  };

*/

#include <iostream>
#include <vector>

using namespace std;

namespace decltype_ex {

class Test {};

void example() {
  int x(42);

  // decltype with lvalue variable
  decltype(x) y(0); // The type of y is int

  // decltype with lvalue expression
  decltype((x)) p(x); // The type of p is lvalue reference to int

  // decltype with prvalue
  decltype(42) z; // The type of z is int

  // decltype with xvalue expression
  decltype(Test()) t; // The type of t is Test&&
}

} // namespace decltype_ex
namespace decltype_auto_ex {
void example() {
  const int a(99);      // The type of a is const int
  auto b = a;           // The type of b is int
  decltype(auto) c = a; // The type of c is const int

  cout << "b = " << b << ", c = " << c << endl;
  ++b;
  //++c;                              // Error!
  cout << "b = " << b << ", c = " << c << endl;
}

} // namespace decltype_auto_ex

namespace decltype_apps {

// Return the sum of two arguments of any type
template <typename T, typename U> auto add(T t, U u) -> decltype(t + u) {
  return t + u;
}

// Return a vector of n elements, initialized with value x
auto make_vector = [](auto x, size_t n) { return vector<decltype(x)>(n, x); };

void example() {
  cout << "add(2, 3) => " << add(2, 3) << endl;
  cout << R"(add("Hello", 2) => )" << add("Hello", 2) << endl;
  cout << R"(make_vector(2,3) => )";
  auto vint = make_vector(2, 3);
  for (auto i : vint) {
    cout << i << ", ";
  }
  cout << "\n";

  cout << R"(make_vector("Hello",2) => )";
  auto vstr = make_vector("Hello", 2);
  for (auto s : vstr) {
    cout << s << ", ";
  }
  cout << "\n";
}

} // namespace decltype_apps

int main() {
  const int x{42};
  auto y = x;       // The type of y is int
  decltype(x) z{0}; // The type of z is const int

  cout << "y = " << y << ", z = " << z << endl;
  ++y;
  //++z;                           // Error!
  cout << "y = " << y << ", z = " << z << endl;
  std::cout << "+-----------------decltype_auto_ex-----------------+\n";
  decltype_auto_ex::example();
  decltype_apps::example();
}

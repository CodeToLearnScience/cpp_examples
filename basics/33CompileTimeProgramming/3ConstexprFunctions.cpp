/*
-----------------------
constexpr functions
-----------------------
- C++11 has constexpr functions
  * Arguments are constant expressions
  * Return a constant expression
  * Executed at compile time
  * Implemented using a compile-time interpreter which supports most of C++
  * Written in normal C++ code
  * Understandable error messages!

- To make a function constexpr, we put the constexpr keyword before its return
type

   constexpr double miles_to_km(double miles) {return miles*1.602;}

- A constexpr function must be "pure"
  * It cannot modify its arguments
  * Cannot modify global/static variables

- A constexpr functions are implicitly defined as inline because function call
is omitted
  * Multiple definitions allowed
  * Can be used in header-only libraries

----------------------------
Run-time constexpr functions
----------------------------
- A constexpr function can be called with arguments that are not constant
expressions
- In this case, the return value will not be a constant expression
  * If the return value needs to be a constant expression, this is an error
-  The function will be evaluated at runtime, like other functions
- This avoids the need to write an otherwise identical version for variables

------------------------------------
Applications of constexpr functions
------------------------------------
- constexpr functions are useful for performing calculations at compile time
  * The calculation is done once (during the development process) instead of
    every time the program is run
  * No runtime overhead
  * Reduces energy consumption

-------------------------------------
constexpr functions in C++14
-------------------------------------
- In C++11, the body of a constexpr function could only contain a single return
statement
- In C++14, these requirements were relaxed and constexpr functions can contain
  * Multiple statments
  * variable declarations (must be initialized, non-static)
  * Flow control - if, switch and loops, including range-for-loops
- However, the body of a constexpr function may not contain any code which
causes an action at runtime
  * e.g. new/delete, calling virtual function, throwing exception
  * So you can't use string and vector

----------------------------------------
constexpr member functions
----------------------------------------
- A member function can be made constexpr
  * Takes constant expression arguments
  * Returns a constant expression
- This is a different restriction from a member function which is const
  * cannot modify "this"
- In C++11, constexpr member functions were also const
  * Returned a constant expression, could not modify "this"
- In C++14, constexpr member functions are allowed to modify "this"
  * Unless also declared as const

-----------------------------
constexpr members
-----------------------------
- Classes and structs can have members which are constexpr
  * initialized from constexpr
  * Cannot be modified
- These must also be declared static
- otherwise, the data members will not be available at compile-time
*/

// constexpr function
constexpr double miles_to_km(double miles) { return miles * 1.602; }

// the argument is a constexpr
// The return value is a constexpr
// The function is evaluated at compile-time
const double dist1 = miles_to_km(40);

// The argument is not a constant expression
// The Return value is not a constexpr
// The function is evaluated at run time
double arg{40};
double dist2 = miles_to_km(arg);

// The argument is not a constexpr
// The return value is not a constexpr
// The return value is required to be a constexpr - Error

// constexpr double dist4 = miles_to_km(arg);

int main() {}

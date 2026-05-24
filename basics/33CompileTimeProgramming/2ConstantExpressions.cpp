/*
------------------------
Constant Expression
------------------------
- A constant expression has a value that is evaluated at compile time and which
cannot change
  * A literal
  * A value computed from literals
  * A value computed from other constant expressions

--------------------------------
Constant expression variables
--------------------------------
- A variable can be a constant expression if
  * It is initialized by a constant expression
  * and it cannot susequently be modified

  //i and j are variables which are constant expressions
  const int i{42}, j{99};

  //i+j is computed from constant expressions
  //i+j is a constant expression
  i+j;

--------------------------------
Constant expression example
--------------------------------
- The dimension of an array must be a constant expression
  const int i{42}, j{99};
  int arr[i+j];           //OK - i+j is a constant expression

- The compiler will check this
  int i{42}, j{99};   // i and j are constant expressions

  //NB compile with -pedantic with g++. Without -pedantic g++ allows this as a
  //not-standard extension.
  int arr[i+j];         //Error - i+j is not a constant expression

-------------------
const keyword
-------------------
- The const keyword is in all versions of C++
- A const variable cannot be modified after it has been initialized
- We can initialize a const variable from a constant expression

  const int i{3};   //cannot change the value of i

- Or from a value which is only known at runtime
  int x;
  cin >> x;
  const int y{x};  //Cannot change the value of y

-------------------
constexpr keyword
-------------------
- C++11 has the constexpr keyword
- This indicates that an variable is a constant expression
- A constexpr variable is
  * evaluated at compile time
  * Cannot be modified

   constexpr int i{3};   // is a constant expression

------------------------
constexpr vs const
------------------------
- A const variable cannot be modified
  * Mainly used for function arguments
  * An argument can be passed by reference (or pointer) to const for efficiency
    and safety
  * The compiler will not allow the called function to modify it
- The constexpr variable has a value which is known at compile time and cannot
be modified
  * Used for computing the values of constants
  * Used to improve performance by doing computation at compile time
*/

#include <iostream>

using namespace std;

int main() {
  const int i{42}, j{99};

  int arr[i + j];
}

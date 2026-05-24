/*
--------------------------------------------------------
# Library-defined operator objects
--------------------------------------------------------
- C++11 defines some generic operator classes in <functional>
  * e.g. less<Type> operator calls the '<' operator of Type
- Arithmetic operators
  * plus, minus, multiplies, divides, modulus, negate
- Relational operators
  * equal_to, not_equal_to, greater, greater_equal, less, less_equal
- Logical operators
  * logical_and, logical_or, logical_not
- Bitwise operators
  * bit_and, bit_or, bit_xor
  * bit_not (C++14)

--------------------------------------
Using Library-defined operator objects
--------------------------------------
- These are functor classes - we need to create an object and call its ()
operator

   less()(t1, t2);   //calls operator <(t1, t2)

--------------------------------------
# Library-defined operator objects
--------------------------------------
- We can use these operators to write generic functions with default comparisons
  * Similar to algorithms (e.g. std::sort)
- We start with a template function which takes a callable object as one of its
arguments

// template function with parameters T and Func
template <typename T, typename Func>
bool compare(const T& t1, const T& t2, Func func) {
    return func(t1, t2);  //call the function
}

--------------------------------------
# Default template argument
--------------------------------------
- We then make Func a default template argument
- We make the callable object a default argument to compare()

  template <typename T, typename Func = less<T>>
  bool compare(const T& t1, const T& t2, Func func = Func()) {
    return func(t1, t2);
  }

- If we provide a callable object, the instantiate function will call it
   compare(x, y, [](int i1, int i2) { return i1 < i2; });

- If not, the instantiated function will call the library's less<T> operator
   compare(x, y);
*/

#include <functional>
#include <iostream>

using namespace std;

// Function template with parameter Func
// If caller does not provide a callable object, use T's operator <
template <typename T, typename Func = less<T>>
bool compare(const T &t1, const T &t2, Func func = Func()) {
  return func(t1, t2);
}

int main() {
  int x{1}, y{2};
  cout << "x = " << x << ", y = " << y << endl;

  // Calling compare with lambda
  auto b = compare(x, y, [](int t1, int t2) { return t1 < t2; });
  cout << "Result of calling compare with lambda: " << boolalpha << b << endl;

  // Calling compare with default:
  auto b2 = compare(x, y);
  cout << "Result of calling compare with default: " << boolalpha << b2 << endl;

  return 0;
}

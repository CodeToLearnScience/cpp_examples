/*
--------------------------------------
assert()
--------------------------------------
- C++ inherited assert() from C
  * Defined in <cassert>
- This checks its argument at runtime. If the argument is zero, it calls
std::abort(). Otherwise, the program continues normal execution
- Useful for checking invariants
  assert (x == 42);                    // x should have the value 42 here
- Can be disabled by #define NDEBUG

--------------------------------------
static_assert()
--------------------------------------
- C++11 provides static_assert()
- It takes a constant bool expression and a string literal (not a c++ library
string)
- The bool expression is checked during compilation
- If false, the compilation stops and the string literal will be used in the
compiler's error message
- Otherwise, the compilation continues normally
  static_assert(sizeof(int*) == 8, "This program requires a 64-bit computer");
- Mainly used in template metaprogramming
  static_assert(std::is_copy_constructible<T>::value,
                "Argument must be copyable");

--------------------------------------
Default Template Parameters
--------------------------------------
- We can write a template class which has default parameters

  template <typename T = int>
  class number {
      T value;                         // value will have type int by default
  };

- If we are not using the default parameter, we instantiate as usual

  // Instantiate a number with long double
  number<long double> high_precision(1.99999);

- To instantiate with the default parameter, we leave the <> empty

  // Instantiate a number with int
  number<> default_number(2);

--------------------------------------
# Instantiation with Default Parameters
--------------------------------------
- From C++11, we can also write a template function with default parameters

  template <typename T = int>
  void func(const T& t1, const T& t2) {
    ...
  }

- We call the function as normal

  // Instantiate the function with deduced types of x and y
  func(x, y);

*/

#include <iostream>

static_assert(sizeof(int *) == 8, "This program requies a 64-bit compiler");

template <typename T = int> class number {
  T value;

public:
  number(const T &value) : value(value) {}
  void print() { std::cout << "value: " << value << "\n"; }
};

template <typename T = int> void func(const T &t1, const T &t2) {
  std::cout << "The sum of " << t1 << " and " << t2 << " is " << (t1 + t2)
            << "\n";
};

int main() {
  // Instantiate number object with long double
  number<long double> high_precision(1.99999);

  // Instantiate number object with int (default)
  number<> default_number(1.99999);

  high_precision.print();
  default_number.print();

  std::cout << "------------function Instantiation with default "
               "parameters---------\n";
  long double hp1{1.99999}, hp2{3.0004};

  int normal1{2}, normal2{3};

  // Instantiate function with long double
  func(hp1, hp2);

  // Instantiate function with int
  func(normal1, normal2);
}

/*
-----------------------------
Constexpr If Examples
-----------------------------
- Allows branches to be evaluated at compile time
- The compiler ignores paths which are not taken

  if constexpr ( // "expr"//) {
   ...               // This code is compiled if "expr" is true
  }
  else {
  ...              // This code is compiled if "expr" is false
  }

----------------------------
# Fibonacci Number
----------------------------
// Recursive function, executed at run-time
  int fibonacci(int n) {
    if (n > 1)
        return fibonacci(n-1) + fibonacci(n-2);
    return n;
  }
*/

#include <iostream>

using namespace std;

namespace fibonacci_with_template_specialization {

// General case (N > 1)
template <int N> int fibonacci() {
  return fibonacci<N - 1>() + fibonacci<N - 2>();
}

// Specialization for N == 1
template <> int fibonacci<1>() { return 1; }

// Specialization for N == 0
template <> int fibonacci<0>() { return 0; }
void example() {
  constexpr int n{10};
  std::cout << "Fibonacci number " << n << " is: " << fibonacci<n>() << "\n";
}
} // namespace fibonacci_with_template_specialization

namespace fibonacci_with_constexpr {
template <int N> constexpr int fibonacci() {
  if constexpr (N > 1) {
    return fibonacci<N - 1>() + fibonacci<N - 2>();
  }
  return N;
}

void example() {
  constexpr int n{10};
  std::cout << "Fibonacci number " << n << " is: " << fibonacci<n>() << "\n";
}

} // namespace fibonacci_with_constexpr

namespace variadic {

template <typename T> void func(T t) {
  cout << "Non-variadic template";
  cout << "Processing argument " << t << endl;
}

template <typename T,
          typename... Args> // Args is a list of types (template parameter pack)
void func(T t,
          Args... args) { // args is a list of arguments whose types match Args
  cout << t;
  size_t size = sizeof...(args) +
                1; // sizeof...(args) returns the number of elements in args
  cout << "Processing argument " << t
       << " and compiler has deduced variadic call with " << size
       << " argument(s) \n";
  func(args...);
}

void example() {
  int i{42};
  double d{0.};
  string s{"text"};
  func(i, d, s);
}

} // namespace variadic

namespace variadic_with_cpp17 {
template <typename T,
          typename... Args> // Args is a list of types (template parameter pack)
void func(T t,
          Args... args) { // args is a list of arguments whose types match Args
  size_t n_args = sizeof...(args) + 1;
  cout << "Variadic template compiler has deduced variadic call with " << n_args
       << " argument(s) \n";
  cout << "Processing argument " << t << endl;
  if constexpr (sizeof...(args) > 0) {
    func(args...);
  }
}

void example() {
  int i{42};
  double d{0.};
  string s{"text"};
  func(i, d, s);
}

} // namespace variadic_with_cpp17

int main() {
  fibonacci_with_template_specialization::example();
  fibonacci_with_constexpr::example();
  variadic::example();
  variadic_with_cpp17::example();
}

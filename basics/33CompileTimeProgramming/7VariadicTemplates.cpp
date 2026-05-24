/*
 -------------------------------------
 Variadic Templates
 -------------------------------------
- A variadic function can take any number of arguments
- In the declaration of a variadic function, the last parameter is ...
   // printf is C library function
   // It takes a format string followed by variable number of arguments
   int printf(const char *fmt, ...);
- Not type-safe
  * printf("%s", 42);     // Oops!
- Only works properly with C types
- The arguments are processed at run time

-------------------------------------
# Variadic Function Templates
-------------------------------------
- C++11 introduced variadic template functions. They are done at compile time
Efficient and type-safe
- The list of template parameter types is written as typename... T
- The list of function parameter types is written as T...
   // template function with a variable number of arguments
   template<typename... Args>   //Args is a list of template parameter types
   void func(Args... args);     // args is a list of arguments where types
                                // match Args
- These ... lists are known as "parameter packs"

-------------------------------------
# Type deduction
-------------------------------------
- The compiler will deduce the number of arguments and their types from the call
  template <typename... Args>     //Args is a list of types (template parameter
                                  //pack)
  void func(Args..., args);       //args is a list of arguments whose types
                                  //match Args

  // Equivalent to template<typename T>
  // func(T t);
  // func("hello"s);     // Instantiated as func(string);

  // Equivalent to template<typename T, typename U, typename V>
  // func(T t, U u, V v);
  func(42, 0.0, "text"s);     // Instantiated as func(int, double, string);

-------------------------------------
# Parameter Packs
-------------------------------------
- Parameter packs are only available at compile time
- We can do three things with a parameter pack:
  * Use sizeof...() to get the number of elements
  * Use make_tuple() to store them in a std::tuple (this is useful as this makes
    arguments available at runtime)
  * Iterate over the elements, using template recursion


-------------------------------------
# Template Recursion
-------------------------------------
- We can have recursive template function calls

  template <typename T, typename U, typename V>
  void func(T t, U u, V v) {
      func(u, v);                    // Recursive call
  }

  template <typename U, typename V>
  void func(U u, V v) {
      func(v);                       // Recursive call
  }

  template <typename V>
  void func(V v) {
      // End of recursion
  }

-------------------------------------
# Pack Processing
-------------------------------------

- We can process a variadic template's pack by making recursive calls
- Each call removes the first element from the list

  template <typename T, typename... Args>
  void func(T t, Args... args) {
      // Process t here

      // The compiler will replace args... by the list of arguments
      func(args...);    // Recursive call, passing the remainder of the list
  }


-------------------------------------
# Terminating the Recursion
-------------------------------------
- To terminate the recursion, we write another template with a single argument
- This will be passed the final element in the list

  template <typename T>
  void func(T t) {
      cout << "The last argument is " << t << endl;
  }

- This must be declared above the variadic template in the source code

*/
#include <iostream>
#include <string>

using namespace std;

// Args is a list of types (template parameter pack)
// args is a list of elements whose types match Args
template <typename... Args> void func(Args... args) {
  cout << "Compiler has deduced call with " << sizeof...(args)
       << " argument(s)\n"; // remember ...(dots after sizeof)
}

// Args is a list of types (template parameter pack)
// args is a list of elements whose types match Args
template <typename... Args> void func1(Args... args) {
  auto arg_tuple = make_tuple(args...); // Store arguments in a tuple
  auto first_tuple = get<0>(arg_tuple); // Store first argument in tuple
  cout << "First argument is " << first_tuple << endl;
}

namespace recursion {

template <typename T> void func(T t) {
  cout << "Non-variadic templates\n";
  cout << "Processing argument " << t << endl;
}

// Args is a list of types (template parameter pack)
template <typename T, typename... Args>
// args is a list of arguments whose types match Args
void func(T t, Args... args) { // every recursion call t takes first arg from
                               // args pack (here d=0.0 and then string s=text)
  size_t n_args = sizeof...(args) + 1;
  cout << "Variadic teamplate: compiler has deduced variadic call with "
       << n_args << " argument(s)" << endl;
  cout << "Processing argument " << t << "\n";
  func(args...);
}

void example() {
  cout << "\n---------------variadic recursion-------------------\n";
  int i{42};
  double d{0.};
  string s{"text"};
  func(i, d, s); // Instantiated as func(int, double, string);
}

} // namespace recursion

int main() {
  int i{42};
  double d{0.0};
  string s{"text"};

  func(s);        // Instantiated as func(string);
  func(i, d, s);  // Instantiated as func(int, double, string);
  func1(i, d, s); // Instantiated as func(int, double, string);

  recursion::example();
}

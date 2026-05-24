/*
----------------------------------
# Constexpr If
----------------------------------
- constexpr if was added in C++17**
  - Also known as "if constexpr" or "static if"
- One of the most requested changes to C++!**
- Allows conditionals to be evaluated at compile-time**
- Conditionals can be evaluated at compile-time

  if constexpr (a < b)
    ...
  else
    ...

- Can be used for conditional compilation
  * Only the "true" branch is compiled into the program
  * The "false" branches are ignored by the compiler
- If "a" is less than b, then the compiler will evaluate that part of the code
and compile it into the program. So the interesting point here is that only the
branch which is taken gets included in the program

----------------------------------------------------------
Constexpr If vs Preprocessor Directives
----------------------------------------------------------
- C++ has preprocessor directives which can be used for conditional compilation
  * #if and #ifdef conditionally include or exclude code from compilation
- C++ preprocessor directives have a number of drawbacks
  * Simple text-based substitution
  * The preprocessor does not understand types or C++ syntax
  * Arguments are not evaluated (operator precedence, side-effects)
- constexpr if is executed during compilation proper
  * Has access to all the compiler's internal data
  * In particular, type information

----------------------------------
String Helper Function
----------------------------------
-  Suppose we want a function that can take either std::string or a built-in
type
    // Pseudo-code
    string get_string(arg) {
        if (arg's type is std::string) //std::to_string does not support
                                       //std::string
          return arg;                  //Return the argument if it is a string
        else
            return std::to_string(arg); //convert the argument to a string
    }

- We will write this as a template function which checks the argument's
type traits

----------------------------
Runtime If Statement
----------------------------
We use the standard C++ if statement

  template<typename T>
  string get_string(const T& arg) {
    if (std::is_same<std::string, T>::value)  // Replaced by "true" if T is a
                                              // string, else "false"
      return arg;                            // T is std::string
    else
      return to_string(arg);                 // T is a built-in type
    }

--------------------------------
Template Specialization
--------------------------------
- What people did before C++17
-  The problem could also by solved using template specialization

    template<typename T> //template function for the general case
    string get_string(const T& arg) {
        return to_string(arg);
    }

    template<>  // Template specialization for std::string
    string get_string(const string& arg) {
        return arg;
    }

- Two functions to perform a single task
- Must be kept in the correct order

-------------------------------
Advantages of Constexpr If
-------------------------------
- Template Specialization
    * Requires multiple functions which need to be in a specific order
    * Only suitable for simple conditionals

- SFINAE and enable_if
    * Complex and obscure code
    * Difficult to get right
    * Hard to maintain

- constexpr if
    * Single function with normal-looking code
*/

#include <iostream>
#include <string>
#include <type_traits>

using namespace std;
// this will not compile because we have an "if" statement, C++ says that all
// the branches must compile, even if they are never taken
// But if we chage if to if constexpr, then it will
template <typename T> string get_string(const T &arg) {
  // Replaced by "true" if T is a string, else "false"
  if constexpr (std::is_same_v<std::string, T>) {
    return arg; // Error if T is a built-in type

  } else {
    return to_string(arg); // Error if T is std::string
  }
}

namespace with_template_specialization_before_cpp_17 {
// template function for the general case
template <typename T> string get_string(const T &arg) { return to_string(arg); }
// template specialization for std::string
template <> string get_string(const string &arg) { return arg; }

void example() {
  int x{42};
  cout << "x: " << x << " " << endl;
  cout << "get_string(x): " << " " << get_string(x) << " " << endl;
  string str{"hello"};
  cout << "str: " << str << " " << endl;
  cout << "get_string(str): " << " " << get_string(str) << " " << endl;
}

} // namespace with_template_specialization_before_cpp_17

// So when you have overloaded template functions, the compiler will only
// consider the ones which instantiated. If one of these overloads cannot be
// instantiated, then the component will just ignore it
namespace sfinae {
// not instantiated if T is std::string
template <typename T,
          std::enable_if_t<!std::is_same_v<std::string, T>, int> = 99>
string get_string(const T &arg) {
  return to_string(arg);
}

// instantiated  only if T is std::string

template <typename T,
          std::enable_if_t<std::is_same_v<std::string, T>, int> = 99>
string get_string(const T &arg) {
  return arg;
}

void example() {
  int x{42};
  cout << "x: " << x << " " << endl;
  cout << "get_string(x): " << " " << get_string(x) << " " << endl;
  string str{"hello"};
  cout << "str: " << str << " " << endl;
  cout << "get_string(str): " << " " << get_string(str) << " " << endl;
}

} // namespace sfinae

int main() {
  int x{42};
  cout << "x: " << x << " " << endl;
  cout << "get_string(x): " << " " << get_string(x) << " " << endl;
  string str{"hello"};
  cout << "str: " << str << " " << endl;
  cout << "get_string(str): " << " " << get_string(str) << " " << endl;

  std::cout << "\n------------with template specialization--------------\n";
  with_template_specialization_before_cpp_17::example();

  std::cout << "\n------------with substitution failure is not an "
               "error--------------\n";
  sfinae::example();
}

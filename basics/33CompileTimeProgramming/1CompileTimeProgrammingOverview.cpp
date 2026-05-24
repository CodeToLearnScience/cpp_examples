/*
-----------------------------
Compile-time programming
-----------------------------
- In Compile-time programming, the compiler executes code at compile-time
- The result of the computation is available in the program. This means that,
when the program runs, it instantloy has access to the result, and does not need
to perform any calculation itself. So that means the operation takes zero time.
So obviously being able to do this is very desirable, but there are practical
limitations on what you can do, and how easily you can do it.
- No run-time overhead
- Compile-time programming could be done in C
- Uses pre-processor "macro functions"
  * Copy and paste with substitution
  * No type information
  * Does not understand C++ syntax
  * Error-prone

    #define Max(x, y) ((x)>(y)?(x):(y))
    Max(++a, b);     //replaced by ((++a)>b?(++a):(b))
                     //a maybe incremented twice

- So the preprocessor is the very first stage of compilation. This is when the
compiler goes through and removes comments, compresses whitespaces and so on.
You can give directives to the preprocessor, which start with a hash symbol.
One of the directives you can give is to define a symbol. So you can put hash
define some symbol. And preprocessor will replace that symbol by whatever you
define it as. And you can provide arguments, and then the arguments will be
substituted.

---------------------------------------
Template Programming Features
---------------------------------------
- Traditional C++ has templates
- These were intended to support generic programming
- Later discovered to provide a Turing-complete programming language!. That
means that, in theory, you can solve any problem using templates. If you are
masochistic enough! :D
  * Template parameters can represent state variables
  * Recursive instantiation can simulate loops
  * Template specializations to implement control flow
  * Integer operations to calculate results

----------------------------------
Template Metaprogramming
----------------------------------
- Mainly done by library developers
- Compile-time programming
- Writing generic code to avoid duplication
  * e.g STL
- Making decisions at compile time for efficiency and/or portability
  * e.g. use of hardware-specific features
- Domain-specific programming
  * e.g. customized language
- Expressing complex software patterns and concepts
- Mostly uses class templates rather than functions
- By convention
  * Members that represent numeric results or other values are named "value"
  * Members that represent types are named "type"
- Makes heavy use of teplate specialization
- Use of "type traits" (C++11) to get information about the properties of types

  * e.g. is_arithmetic<T>

---------------------------------
Compile-time programming
---------------------------------
- Templates
  * Clumsy and verbose syntax
  * Logical operations are complicated
  * Incomprehensible error messages
  * No debugger support. A debugger requires a running program in memory, and
    these are actaully inside the compiler
- C++11 also provdes constexpr
  * The compiler executes normal C++ code
  * Understandable error messages!
*/

#include <iostream>
#include <type_traits>
// 1. no type safety
// 2. because of operator precedence, we need to put parenthesis around x and y
// 3. And if arguments have side effects, then they will be evaluated more than
// once
#define Max(x, y) ((x) > (y) ? (x) : (y))

namespace template_ex {
class A {};
void example1() {
  std::cout << std::boolalpha;
  std::cout << "is_arithmetic<int>: " << std::is_arithmetic<int>::value
            << "\n"; // true
  std::cout << "is_floating_pont<int>: " << std::is_floating_point<int>::value
            << "\n";                                               // false
  std::cout << "is_class<A>: " << std::is_class<A>::value << "\n"; // true
  std::cout << "is_pointer<const char*>: "
            << std::is_pointer<const char *>::value << "\n"; // true
}

} // namespace template_ex
int main() {

  int a{5}, b{2};
  std::cout << "a = " << a << ", b " << b << "\n";
  std::cout << "Max(a, b): " << Max(a, b)
            << "\n"; // replaced by ((a)>(b)?(a):(b))
  std::cout << "a = " << a << ", b " << b << "\n";
  std::cout << "Max(++a, b): " << Max(++a, b) << "\n"; //((++a)>b?(++a):(b))
  std::cout << "a = " << a << ", b " << b << "\n"; // a may be incremented twice

  std::cout << "\n-------------------------------------------------------\n";
  template_ex::example1();
}

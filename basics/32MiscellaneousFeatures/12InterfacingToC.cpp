/*
 ----------------------
 Interfacing to C
 ----------------------
 - Many interfaces are written in C
   * Operating system API
   * Database API
   * Third-party libraries and frameworks
   * Languages with "foreign function" interfaces (many interpreted Languages)`

-------------------------------------
Source Code Compatibility
-------------------------------------
- C is an almost complete subset of C++
- Almost any C program is a legal C++ program
  * C code can use C++ reserved words
  * C99 introduced some incompatible features
- The simplest solution is to compile the entire program's source code with a
C++ compiler
- May not always be possible
  * C code contains incompatibilities
  * C code requires a complex build process
  * The C source code is not available

--------------------------------
Binary Compatibility
--------------------------------
- Interfacing with C at the binary level requires. Unfortunately, there is no
standard on binary interface in C or C++. So the compilers you use have to
agree on various things
  * A header file which declares the functions in the C interface
  * The compiled binary code for the functions
  * This can be an object file, a static library or DLLs/shared object
- The C and C++ compilers used must be compatible
  * Same object file format
  * Same function call conventions
  * Same word size (32-bit vs 64-bit)
- If any C++ library features are used, use a C++ compiler to link the binary

------------------------------
Name Mangling
------------------------------
- We need to be aware of "name mangling" (Microsoft calls is decoration)
  * In C, a function has the same name in the binary object file as it does in
  the source code
  * In C++, the compiler "mangles" the name. This is required to support
  function overloading
    - int func(int x);         //Symbol name is _Z3func1i (with g++)
    - double func(double x);   //Symbol name is _Z3func1d (with g++)

----------------------------------
The Extern "C" Directive
----------------------------------
- Name mangling does not occur in C
  * C does not support overloaded functions
- To make C++ binaries compatible with C, we use the extern "C" directive
- This tells the C++ compiler not to mangle the function name
  extern "C" int func(int x);     //symbol name will be func
- We can declare multiple symbols as extern "C"

  extern "C"{
    int func(int x);
    double dfunc(double x);
  }

- We can also declare all the symbols in an include file as extern "C"
  extern "C" {
    #include "cstuff.h" //symbol names in cstuff.h will not be mangled
  }

-----------------------------------
Exporting to C
-----------------------------------
- When writing C++ function that will be called from C
  * Use built-in types only in the inteface - e.g., char, int, double
  * Can also use arrays and pointers to built-in types
  * or Structs which have members of built-in types only
- Put the functions in the global namespace
  * C has no concept of namespace

------------------------------------
Conditional Compilation
------------------------------------
- The interface header will be processed both as C and C++
- It may contain some things which are not valid C
  * e.g the extern "C" directive
- We can use the __cplusplus preprocessor symbol
  * This is defined by C++ compilers, but not by C compilers
- We use a conditional compilation to hide things from the C compiler

  #ifdef __cplusplus
  extern "C"  //Compiling C++ code - use extern directive
  #else
  ...         // Compiling C code - do not use extern directive
  #endif

-------------------------
Resource Management
-------------------------
- C uses malloc() and free()
  * C does not have new and delete
- C uses raw pointers for resource management
  * No destructors, no RAII, no smart pointers
  * Resource pointers are passed to a "tidy-up" function
  * Alternatively, memory is released by the user when no longer required
- Important to be clear about this
  * Read the documentation!
  * (or the source code)

----------------------------------------------
Converting Sequential Containers to Arrays
----------------------------------------------
- std::string and std::vector have a data() member function
- This returns a pointer to the container's internal memory buffer
- This can be used as a built-in array

  std::string s{"Data to export"};
  const char *ps = s.data(); //get the character as a null-terminated array

  vector<int> vec{3, 1, 4, 1, 5, 9};
  vec.data();   //get the element

---------------------------------------------
Converting Associative Containers to Arrays
---------------------------------------------
- For associative containers, we can use the copy alogorithm to populate a
vector
  std::set<int> numbers;
  ...
  copy(begin(numbers), end(numbers), back_inserter(vec));
  vec.data(); //get the elements as an array

- For maps, populate separate vectors for keys and values
  std::map<int, int> m;
  ...
  for(auto el: m){
    key.push_back(el.first);
    values.push_back(el.second);
  }
*/

#include "12a_Add.h"
#include <stdio.h>

int main() { printf("add(2,3) returns %d\n", add(2, 3)); }

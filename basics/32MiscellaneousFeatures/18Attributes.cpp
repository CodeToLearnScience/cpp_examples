/*
-------------------
Attributes
-------------------
- There are various implementation-dependent compiler directives
  * #pragma
  * __attribute
  * __declspec
- C++11 introduced attributes to provide a standard syntax for these
  * It also defines a few attributes in the language
- Attributes give extra information to the compiler
- They should not be used to extend the language or change the meaning of the
program

-----------------------
Attribute Syntax
-----------------------
- An attribute goes inside a pair of double square brackets
  [[noreturn]]
- In declarations, attributes go before the entity they apply to

   [[noreturn]] void server();

- An attribute can be in namespace

   [[gnu::always_inline]]

- Attributes can take arguments

  [[deprecated("Use the version 2.0 interface in new code")]]

-------------------------
C++11 Attributes
-------------------------
- [[noreturn]] indicates that a function does not return

   [[noreturn]] void server(){
     while(true){
       //process incoming connections
     }
   }

- The aligns keyword is used for memory alignment
  //aligns the array "buffer" on 16-byte boundaries

  alignas(16) char buffer[128]; //It's not actually an attribute, but meant to
                                //replace the hash pragma pack. But it only
                                //works if the argument is greater than the word
                                //size

-------------------------
C++14 Attributes
-------------------------
- C++14 added [[deprecated]]
- This causes a compiler warning if the object is used

  [[deprecated]] void func();

- It has an optional argument for an explanation string

   //this will give a compiler warning whenever func() is called
   [[deprecated]] ("Use the version 2.0 interface in new code")]]
   void func();

----------------------
fallthrough Attribute
----------------------
- C++17 provides a [[fallthrough]] attribute
- This indicates that the break statement is intentionally omitted and the
compiler should not give a warning

    switch (c){
      case '':
          //no break statement - could be a mistake?
      case '\t':
          [[fallthrough]] //Fall through to next case - not a mistake
      case '\n':
          ++ws_count;
          break;

    }

------------------------
nodiscard Attribute
------------------------
- C++17 provides a [[nodiscard]] attribute
- The compiler will give a warning if a nodiscard function is called and its
returned value is ignored

  //Function whose return value should not be ignored
  [[nodiscard]] int func(){
    return 99;
  }

  func(); //call func and ignore its returned value - compiler warning

- Attributes can also be used for
  * Variables
  * Types
  * Members of structs and classes, etc.
- For struct, class and enum, the attribute goes before the type name

  //Nodiscard type
  //All functions which return Test are nodiscard
  struct [[nodiscard]] Test{};
*/

#include <iostream>

[[noreturn]] void server() {
  while (true) {
    // process incoming connections
  }
}

// this will give a compiler warning whenever func() is called
[[deprecated("Use the version 2.0 interface in new code")]]
void func() {
  std::cout << "I've been deprecated\n";
};

[[nodiscard]] int func1() { return 99; }

struct [[nodiscard]] Test {};

Test func2() { return Test{}; }

int main() {
  func();
  func1();
  func2();
  server();

  // This could be useful if you have a function where you declare all the
  // variables, but you want to test the function before you have finished it.
  // So you may have some variables which are temporarily unused. So this will
  // get rid of annoying warnings
  [[maybe_unused]] char buffer[128]; // unreferened warning goes away
}

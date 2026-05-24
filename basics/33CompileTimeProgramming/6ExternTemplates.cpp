/*
 ----------------------------
 Extern Templates
 ----------------------------
 - Extern templates are a useful way of addressing the problem of "bloating"

 ---------------------
 Template Bloat
 ---------------------
 - Imaging we have some code like this
   //Header.h
   template<typename T> void func(arg<T>){...}

   //File_001.cc
   func(this_string);      //instantiates func(string) in File_001.cc


   //File_269.cc
   func(this_string);     //instantiates func(string) in File_269.cc

- The compiler will instantiate a separate func(string) in every File_nnn.cc. So
we end up with hundreds of source code files, which contain the same
instantiation code.
- Every File_nnn.o will contain the binary code for func(string)
  * However, the linker will remove the duplicate definitions from the
    executable
- This "template bloat" increases object file size and compile time
- This can be a serious problem in large projects
- The traditional way of doing this, is to manually instantiate the templates
as shown in example 6ExternTemplates.h

--------------------------
extern keyword
--------------------------
- The extern keyword was inherited from C
- It turns the definition of an uninitialized into a declaration
- Used to make a global variable accessible across source files (although very
bad idea. This is why OOP was invented in fact, because global variables were
causing so many problems)

  //source1.cc
  extern int meaning_of_life;   //declare meaning_of_life
  meaning_of_life = 42;

  //source2.cc
  extern int meaning_of_life;  //declare meaning_of_life
  cout << meaning_of_life;

- There must be exactly one file where the variable is defined and must not be
initialized
  //source_impl.cc
  int meaning_of_life;  //define meaning_of_life

- We can declare a variable as extern, in a source file or in a header and this
means that the actual variable is defined somewhere else. So this is just the
declaration of the variable. And then we can use this in different source files
So the one file (source_impl.cc) where int meaning_of_life is declared actual
define the meaning_of_life variable and the ones in the other source code are,
if you like, references to this one. Not the references that we have in C++,
but sort of "link-time" references

-------------------------------
extern template
-------------------------------
- In C++11, extern can also apply to templates
- Declare the instantiation as an extern template (this must come after the
tempalte definition)

//header.h
template<typename T> void func(arg<T>){...}
extern template void func(string);   //declares func(string) as instantiated
                                     //elsewhere

//in File_001.cc...File_269
//Call func(string) instantiated elsewhere

- There must be exactly one file where the function is instantiated
//impls.cc
template void func(string); //compiler will instantiate func(string) here

-----------------------------
Class Templates
-----------------------------
- This works the same way with class templates
 //Header.h
 template <typename T> class Test{...}
 extern template class Test<int>; //declare Test<int> as instantiated elsewhere

 //In File_001.cc ... File_269.cc
 //Use Test<int> instantiated elsewhere

 //Impls.cc
 template class Test<int>; //compiler will instantiate Test<int> here
*/

#include "6ExternTemplates.h"

// define the non-template function
void fun(const std::string &str) {
  std::cout << "func() printing " << str << ": ";

  // call the template function
  // The compiler will not instantiate it here (it cannot see the definition)
  print(std::cout, str);
}

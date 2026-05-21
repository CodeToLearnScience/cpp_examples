/*
 ---------------------------------
 Inline Namespace
 ---------------------------------
 - In C++ you can define one namespace iside another
 - In C++11, we can say that the inner namespace is "inline". The difference is
 any symbols which are defined inside the inline namespace B, will appear to be
 defined in A.


 -----------------------------------------------
 Inline Namespaces in C++ Standard Library
 -----------------------------------------------
 - The C++ STL uses inline namespaces

    namespace std{
      inline namespace literals{
        inline namespace string_literals{ //define "s" suffix for std::string//}
        inline namespace chrono_literals{ //define "s" suffix for seconds,etc//}
      }
    }

- We only need a single "using" statement to bring in all literals

  using namespaces std::literals; //brings in symbols from string_literals and
                                  //chrono_literals
  using namespace std;            //brings in symbols from string_literals and
                                  //chrono_literals

--------------------------------
inline namespaces and versioning
--------------------------------
- Inline namespaces are useful for working with different versions of code
  * Version 1 Refrigerator class implements basic refrigerator functionality
  * Version 2 Refrigerator class implements enhanced refrigerator functionality
- We work in a "product" namespace
- We give each version its own namespace inside the "product" namespace

   namespace product{
     namespace version1{
       class refrigerator{//Basic refrigerator defintion//};
     }
     inline namespace version2{
       class refrigerator{//enhanced refrigerator defintion//};
     }
     refrigerator fridge; //uses version1's refrigerator class
   }

- We put the code for the current version in an inline namespace
  * The code for other versions is put in nested namespace inside product
- Without any scope operators, we get the current version of the code
  * If we need a different version, we qualify it with that version's namespace
- When a new version is released, we make that namespace inline and change the
previous version to a nested namespace
- Code that does not use scope operators will automatically start using the new
version
*/

namespace A {
namespace B { // Namespace B is "nested" inside namespace A
int x;        // x is a symbol defined in namespace B

}
// B::x //To use x in namespace A, we must put B:: in front of it

} // namespace A

namespace C {
inline namespace D { // Namespace D is "inline" to namespace C

int x; // x is a symbol defined in namespace D

}
// x; //No need to put D:: here

} // namespace C

int main() {
  A::B::x = 5; // To use x in the global namespace, we put A::B::
  C::x = 5;    // To use x outside the namespace, we can just put C::
}

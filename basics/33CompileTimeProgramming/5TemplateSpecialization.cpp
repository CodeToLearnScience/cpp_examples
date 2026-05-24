/*
--------------------------------
Tempalte Specialization
--------------------------------
- Templates are generic
  * When we write a class or function template, we will get the same behaviour
    for every type that we instantiate it with
- Sometimes we may wish to have different behaviour for some types
  * We want to handle some types differently
  * The code does not behave correctly for some types
  * We want to optimize the code for some types
- We can do this with a "template specialization"

----------------------------------------------
Template Specialization Syntax
----------------------------------------------
//Generic vector class
template <typename T>
class Vector{
...                                    //implement using an array of T
};

//specialization of vector class for bool type
template<>
class Vector<bool>{                   //we leave the <> empty
...                                   //We write the parameter type(s) here
};                                    //Implement using a bitmap

- We have written specialization immediately after generalization, otherwise it
will not compile

-------------------------------------------
Template Ordering in Source Code
-------------------------------------------
- Usually, the specialization follows immediately after the generic template
  * If the specialization comes before the generic template, it will not compile
  * If the generic template is not visible, the specialization will not compile
  * If the specialization is not visible to code that uses it, the compiler will
    instantiate the generic template

---------------------
Instantiation
---------------------
- When a template is instantiated, the compiler has to choose which version to
use
- It will always chosse the most specific alterative which matches

   Vector<bool> vec;   //define a Vector variable

- Vector<bool> is more specific than Vector<T> with T == bool
- The compiler will instantiate the bool specialization

----------------------------------
Partial Specialization
----------------------------------
- Template specialization requires a single type per parameter
- Occasionally we may want to have a family of types instead of a single type
- We can use partial specialization for this
  * Only allowed for class and value templates
  * There are a number of limitations on the arguments

  //generic vector class
  template <typename T>
  class Vector{
  ...
  };

  //partial specialization of Vector class for pointer elements
  template <typename T>
  class Vector<T*>{
  ...
  };

  Vector<int> vec;   //instantiates generic vector
  Vector<int*> vec;  //instantiates partial specialization of Vector class
*/

#include <algorithm>
#include <iostream>
#include <list>
#include <vector>

using namespace std;

// generic vector class
template <typename T> class Vector {
public:
  void identify() { cout << "Vector<T>\n"; }
};

// specialization of vector class for bool type
template <> class Vector<bool> {

public:
  void identify() { cout << "Vector<bool>\n"; }
};

//======================================================
namespace generic_funcs {
// generic reverse function
template <typename T> void Reverse(T &container) {
  cout << "Calling generic Reverse\n";
  std::reverse(begin(container), end(container));
}

// specialization of reverse function for std::list
// list is itself of a class template
// The element type is part of the list's type
// We need to provide a template parameter for std::list's element
template <typename Elem> void Reverse(std::list<Elem> &container) {
  cout << "Calling specialization of Reverse for list<Elem>\n";
  container.reverse();
}

} // namespace generic_funcs

namespace partial_specialization {
// generic vector class
template <typename T> class Vector {
public:
  void identify() { cout << "Vector<T>\n"; }
};

// partial specialization of vector class for pointers
template <typename T> class Vector<T *> {

public:
  void identify() { cout << "Vector<T*>\n"; }
};

void example() {
  std::cout << "\n------------partial specialization-----------------\n";
  Vector<int> vec;
  Vector<int *> par_vec;

  cout << "Vector<int> identify: ";
  vec.identify();
  cout << "Vector<bool> identify: ";
  par_vec.identify();
}
} // namespace partial_specialization

//=======================================================
int main() {
  Vector<int> ivec;
  Vector<bool> bvec;

  cout << "Vector<int> identify: ";
  ivec.identify();
  cout << "Vector<int*> identify: ";
  bvec.identify();

  std::cout << "\n---------------------------------------------------\n";
  std::vector<int> vec{3, 1, 4, 1, 5, 9};
  cout << "vec before calling Reverse()\n";
  for (auto v : vec) {
    cout << v << ", ";
  }
  cout << "\n";
  generic_funcs::Reverse(vec); // Call generic Reverse

  cout << "vec after callign Reverse()\n";
  for (auto v : vec) {
    cout << v << ", ";
  }
  cout << "\n";

  list<int> lis{3, 1, 4, 1, 5, 9};
  cout << "\nlis before calling Reverse()\n";
  for (auto l : lis) {
    cout << l << ", ";
  }
  generic_funcs::Reverse(lis);
  cout << "lis after calling Reverse()\n";

  for (auto l : lis) {
    cout << l << ", ";
  }
  cout << "\n";

  partial_specialization::example();
}

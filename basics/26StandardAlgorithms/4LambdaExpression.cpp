/*We have been using functors or function pointers as the callable object
-------------------
Lambda expressions
-------------------
- These can be thought of as anonymous local functions
- Similar to "closures" in other language

------------------------------------
Implementation of Lambda expressions
------------------------------------
- When the compiler encounters a lambda expression, it will generate code that
  defines a functor
  * This functor will have a unique name chosen by the compiler
  * The function call operator of the functor will have the same body as the
    lambda expression
  * It will have the same return type as the lambda expression
- The compiler will add code to create a functor object

------------------------
Lambda expression syntax
------------------------
- Lambda expressions are anonymous and defined inline
- To define a lambda expression, we put [] for the function name
- We write the function arguments in the usual way
- We write the function body the same way as for an inline function
- If we write this as a single statement that returns a value, the compiler
  will always be able to deduce the return type
  [](int n){return (n%2==1);} //return type deduced as bool
- This statement causes the compiler to create a functor object
- The functor will be equivalent to is_odd

-----------------------------
Example of lambda expression
-----------------------------
//sort the data, using a lambda expression as the predicate
auto odd_it = find_if(cbegin(vec), cend(vec),
    [](int n){return (n%2==0);}); //lambda expression with one argument

------------------------------
Lambda expression return type
------------------------------
- In C++11, the returns type is only deduced if the lambda expression is a
single statement that returns a vale
  * Otherwise, the return type is deduced as void
- For more complex expressions, we need to provide a trailing return type
  [](int n)->bool{
    ...
  }
- In later versions, the return type is always
- In later versions, the return type is always deduced automatically
  * In C++14, it must be the same in all return paths
  * In C++17, this is no longer required
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

// define a functor for the predicate
class is_odd {
public:
  bool operator()(const int n) const { return (n % 2 == 1); }
};

int main() {
  vector<int> vec{3, 1, 4, 1, 5, 9};

  // pass a functor object
  auto odd_it = find_if(cbegin(vec), cend(vec), is_odd());

  // odd_it will be an iterator to the first odd element (if there is one)
  if (odd_it != cend(vec)) {
    cout << "First odd element is: " << *odd_it << "\n";
  }

  // using lambda instead of functor
  auto odd_it1 =
      find_if(cbegin(vec), cend(vec), [](int n) { return (n % 2 == 1); });
  if (odd_it1 != cend(vec)) {
    cout << "First odd element is: " << *odd_it1 << "\n";
  }
}

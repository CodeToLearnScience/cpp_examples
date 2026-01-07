/*
 --------------------------
 Generic lambda expressions
 --------------------------
- In C++14, the compiler can always deduce the return type of a lambda
expression
  * In effect, the return type is implicitly auto
- We can also use "auto" for the type of the arguments to the lambda expression
  * These are known as "generic lambdas" or "polymorphic lambdas"
  * The most requested feature in C++14!
- The compiler will deduce the argument types from the way the lambda expression
is called
- It will use the same rules as for a template function
//The arguments of func can have any type
//So long as the + operator is defined for them
 auto func = [](auto x, auto y){return x+y;};

 func(2,5);
 func(3.14, 4.2);
 func(str1, str2);

 -----------------------------
 Generic lambda implementation
 -----------------------------
 - The compiler generates a functor with a templated function call operator
 class lambda_func{
    public:
    template<typename T>
    T operator() (T x, T y){return x + y;} //lambda expression body
 };

 //create functor object, instantiate its function call operator and call it
  lambda_func()(2,5);
- The above for illustration; as x and y could be different types int and double
--------------------------
Local variables in lambda
--------------------------
- In C++14, we can create variables in the capture specifier
   [y=2] (int x) {return x+y;}; //y is local to the lambda body
- These variables are implicitly "auto" and must be initialized
- They can be mixed with other captures
  [=, &v, y=2]

---------------------------------------
Generalized capture with initialization
---------------------------------------
- These lambda-local variables can be initialized from captures
  int z = 1; //scope's local variable z
  [y=z+1](int x) {return x+y;}; //lambda body's local variable y
- No special syntax is needed to capture z from the enclosing scope
- Note that z in the containing scope, while y is in the scope of the lambda
body

------------------------------------------
Generalized lambda capture implementation
------------------------------------------
- The compiler will generate a functor with a private member which is
initialized using the capture code

  template <typename T>
  class functor{
    T y;
  public:
    functor(T z) : y(z+1){} //initialize y using capture expression
    T operator() (int x) {return x+y;} //lambda expression body
  };

- The compiler then instantiates the functor and calls it
  functor<int> func(z); //intialize functor using outer scope z
  func(x);              // call it

----------------
Capture by move
----------------
- Generalized lambda capture allows capture by move
- This was the 2nd most requested feature in C++14!
*/

#include <iostream>
#include <string>

using namespace std;

int main() {
  string str1{"Hello, "};
  string str2{"World!"};

  auto func = [](const auto &x, const auto &y) { return x + y; };

  cout << "Calling func(2, 5) gives " << func(2, 5) << "\n";
  cout << "Calling func(3.141, 4.2) gives " << func(3.141, 4.2) << "\n";
  cout << "Calling func(3.141, 4) gives " << func(3.141, 4) << "\n";
  cout << R"(Calling func(str1, str2) gives ")" << func(str1, str2) << "\n";

  auto add_two = [y = 2](auto x) { return x + y; }; // y is local to lambda body
  cout << "Calling add_two(2) gives " << add_two(2) << "\n";

  int z = 1; // scope's local variable
  // Lambda body's local variable y
  auto add_z_plus1 = [y = z + 1](int x) { return x + y; };

  cout << "Calling add_z_plus1(5) gives " << add_z_plus1(5) << "\n";
}

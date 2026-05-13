/*
-------------------------
Tuples in C++17
-------------------------
- Constructor Template Argument Deduction (CTAD) works with tuples. That is if
we have a constructor which is templated, we no longer need to provide the type
parameters.
  tuple<int, double, string> tup{1, 2.0, "three"s}; //C++11/14
  tuple tup{1, 2.0, "three"s"};                     //C++17 with CTAD

- A structured binding can be used to unpack tuples

  type<double, int, string> func()       //function returning a tuple
    return {1.0, 2, "three"s};
  }

  auto [d, i, str] = func();  //Use C++17 structured binding to unpack the tuple

- We no longer need to declare the variables and call the tie() function

-----------------------------------------
Unpacking Tuple into Function Arguments
-----------------------------------------
- We can now pass a tuple to a function which has arguments of the same type as
its elements
- To do this, we call std::apply(). One of the new functions of C++, this is for
using more functional style of programming. It takes a callable object as its
first argument, and then it will call this function and pass the rest of the
arguments to this function. So if we have some function pointer as the first
argument, then this will call the function pointer. And the rest of the
arguments will be forwarded
- The first argument is the function to be called
- The second argument is a tuple containing the arguments

  void func(int i, double d, string s);
  apply(func, tuple(1, 2.0, "three"s)); //calls func(1, 2.0, "three"s);

-----------------------------------------------
Unpacking Tuple into Constructor Arguments
-----------------------------------------------
- We can also pass a tuple to a constructor call
- To do this, we call std::make_from_tuple<T>()
  * The template parameter is the class
  * The argument is the tuple
- This allows us to construct an object by unpacking a tuple

  auto test = make_from_tuple<Test>(tup); //Calls Test(1, 2.0, "three"s);
*/

#include <iostream>
#include <string>
#include <tuple>

using namespace std;

tuple<double, int, string> func() {
  // tuple<int, double, string> tup{1, 2.0, "three"s}; //C++11/14
  tuple tup{1, 2.0, "three"s}; // C++17 with CTAD
  return tup;                  // return the tuple from the function
}

void func1(int i, double d, string s) {
  cout << "i = " << i << ", d = " << d << ", s = " << s << "\n";
}

struct Test {
  int i;
  double d;
  string s;
  Test(int i, double d, string s) : i(i), d(d), s(s) {}
  void print() {
    cout << "i = " << i << ", d = " << d << ", s = " << s << "\n";
  }
};

int main() {

  // Use C++17 structured binding
  auto [i, d, str] = func(); // Store all elements in variables
  cout << "The elements returned from tuple are: " << i << ", " << d << R"(, ")"
       << str << R"(")" << "\n";

  cout << "------use of tuple in apply function (functional programming-----\n";
  apply(func1, tuple(1, 2.0, "three"s)); // calls func(1, 2.0, "three"s);

  cout << "-----------use of tuple as constructor argument-------------\n";
  auto test = make_from_tuple<Test>(tuple(1, 2.0, "three"s));
  test.print();
}

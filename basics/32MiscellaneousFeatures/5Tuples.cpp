/*
------------------
Tuples
------------------
- Tuples are related to pairs

------------------------
std::pair review
------------------------
- std::pair is a compund type
- It has two members of any type, accessed as "first" and "second"
- We can create a pair object explicitly

  pair<string, string> wordpair("hello"'s, "there"s);

- Or use make_pair() to create a pair object

  auto wordpair{make_pair("hello"s, "there"s)};

--------------------
std::tuple
--------------------
- C++11 provides an std::tuple type in <tuple>
- Similar to std::pair, but can have any fixed number of elements
- Elements are accessed by index, not by member name
- We can create a tuple object explicitly

  tuple<double, int, string> numbers(1.0, 2, "Three"s);

- Or use make_tuple() to create a tuple object

  auto numbers{make_tuple(1.0, 2, "Three"s)};

-------------------------
Accessing tuple members
-------------------------
- The way we access tuple members is a bit peculiar. Template parameter is the
index
- To access tuple members, we use the templated std::get() function (non-member
function)
- This takes the tuple as argument and uses the element's index as the templated
parameter

  auto x = get<0>(numbers);                  //Store first element in x
  cout << "First element is " << x << endl;
  get<1>(numbers) = 3;                       //Set second element to 3
                                             //confusing name to set. That's
                                             //quite common in C++ :(
- C++14 allows us to use the type as the parameter, if unique

  auto i = get<int>(numbers);       //Store int element in i
  cout << "Value of int element is " << endl;

------------------------
Unpacking a tuple
------------------------
- The std::tie function unpacks all the elements in a tuple into variables
- The number and type of elements must match

  double d;
  int i;
  string str;

  tie(d, i, str) = numbers;    //Store all elements in variables
  cout << "Tuple elements are: " << d << ", " << ii << R"(, ")" << str << R"(")"
       << endl;

------------------------
When to use tuples
------------------------
- Useful for an ad-hoc data type
- If we want somewhere to store data in the short term that
  * Doesn't need member functions
  * Doesn't need special member functions
  * Isn't important enough to merit making a new type
  * Has elements of different types

-----------------------------
Returning multiple values
-----------------------------
- Traditionally we would use a struct to return multiple values from a function
call
  * Create a struct with unique name in namespace
  * Think up names for all the members
  * Populate members one-by-one in the function
  * Copy members one-by-one in the caller

------------------------------------
Returning data with tuples
------------------------------------
- using a tuple requires much less code

  tuple<double, int, string> func(){
    return {1.0, 2, "Three"s};  //return the tuple from the function
  }

  tie(d, i, str);               //unpack the tuple in the caller

- We cannot use auto to deduce the return type
  * tie() is not able to deduce element types
*/

#include <iostream>
#include <string>
#include <tuple>

using namespace std;

tuple<double, int, string> func() {
  return {1.0, 2, "Three"s}; // return the tuple from the function
}

int main() {

  // we can create a tuple instantly explicitly
  tuple<double, int, string> numbers(1.0, 2, "Three"s);

  // or use make_tuple() to create a tuple instance
  // auto numbers {make_tuple(1.0, 2, "Three"s)};

  auto x = get<0>(numbers); // Store first element in x
  cout << "First element is " << x << "\n";

  cout << "Setting second element to 3\n";
  get<1>(numbers) = 3; // set second element to 3

  // C++14 allows us to use the type as the parameter, if unique
  auto i = get<int>(numbers); // Store int element in i
  cout << "Value of int element is " << i << "\n";

  double d;
  int ii;
  string str;

  tie(d, ii, str) = numbers; // Store all elements in variables
  cout << "Tuple elements are: " << d << ", " << ii << R"(, ")" << str << R"(")"
       << endl;

  cout << "---------------use of tuple to return data from function---------\n";
  tie(d, ii, str) = func();
  cout << "Tuple elements are: " << d << ", " << ii << R"(, ")" << str << R"(")"
       << endl;
}

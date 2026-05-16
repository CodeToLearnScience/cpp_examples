/*
-------------------------
Callable Objects
-------------------------
- Callable object is anything which supports the function call operator
- C++ provides several different callable objects
  * Pointer to non-member function (from C)
  * Functors
  * Lambda expressions (Functors written by the compiler)
  * Objects returned from calling bind()
- Sometimes we want to work with different callable objects which have the same
signature, same arguments and same returns types
- The callable objects all have different types. If we have a pointer to a
function which takes string and returns int, this will be a different type from
a Lambda expression which takes string and returns int

-------------------------
std::function
-------------------------
- C++11 provides std::function in <functional>
- This class has a private member which stores a callable object
  * This can be any callable object which has a given signature
- Template class
  * The object's signature is the parameter
    function<bool(const string&)> match_ptr;
- Implemented using inheritance and virtual functions
- std::function performs "type erasure". So if you have a function object, you
cannot tell what type of callable object is in there. You don't know whether it
is a Lambda, or a functor, or anything else.
  * The object's orignal type cannot be recovered

------------------------------
Uses of std::function
------------------------------
- We can declare a function argument as type std::function
  * This can be passed any kind of callable object which has the right signature
- We can create a contaner whose elements are of type std::function
  * This can be populated with any kind of callable object with right signature

---------------------------------------
Limitations of std::function
---------------------------------------
- The function prototype must match the template parameter
  * Does not support overloading
- Run-time overhead
- Invoking the callable object involves indirection
  * Similar ovehead to a virtual function
- May perform a memory allocation
  * The std::function object has a fixed size
  * If the callable object is too large( e.g functor with data members) it
allocates the necessary memory on the heap

-------------------------------------
Alternatives to std::function
-------------------------------------
- std::function should only be used when we need a polymorphic function object
- If you just want some convenient for storing callable object in a variable,
use auto
  * The callable object retains its orignal type
  * It will be called directly, without any runtime overhead

    auto match_ptr = match; //function pointer
    auto match_cat = [v="cat"](const string& t){return match(t,v);}; //Lambda
*/

#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace std::placeholders;

// non-member function
bool match(const string &test) { return test == "cat"; }

// Functor
class functor_match {
public:
  bool operator()(const string &test) { return test == "cat"; }
};

bool bind_match(const string &animal, const string &species) {
  return animal == species;
}

int count_strings(vector<string> &texts,
                  function<bool(const string &)> match_ptr) {
  int tally = 0;
  for (auto text : texts) {
    if (match_ptr(text)) {
      ++tally;
    }
  }
  return tally;
}

int main() {
  vector<string> animals = {"cat",  "dog", "tiger",  "lion",
                            "bear", "cat", "giraffe"};
  int n;
  // function pointer
  cout << "Calling count_strings with function pointer\n";
  n = count_strings(animals, match);
  cout << R"(The vector contains )" << n << R"( occurences of the word "cat")"
       << "\n";

  // functor
  cout << "\nCalling count_strings with functor\n";

  n = count_strings(animals, functor_match());
  cout << R"(The vector contains )" << n << R"( occurences of the word "cat")"
       << "\n";

  // Lambda expression
  cout << "\nCalling count_strings with Lambda expression\n";
  n = count_strings(animals, [](const string &test) { return test == "cat"; });
  cout << R"(The vector contains )" << n << R"( occurences of the word "cat")"
       << "\n";

  // bind object
  cout << "\nCalling count_strings with bind object\n";
  auto match_cat = bind(bind_match, _1, "cat");
  n = count_strings(animals, match_cat);
  cout << R"(The vector contains )" << n << R"( occurences of the word "cat")"
       << "\n";
}

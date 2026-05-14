/*
-----------
std::bind
-----------
---------------------
Function Pointer
---------------------
- Imagine we have a function which compares its argument to a fixed value

  bool match(const string& animal){
    return animal == "cat";
  }

- We can use this function as the predicate in an algorithm call

  vector<string> animals = {"cat", "dog", "tiger", "lion" "cat", "giraffe"};
  count_if(begin(animals), end(animals), match);

--------------------
std::bind()
--------------------
- C++11 defines std::bind in <functional>
- bind() takes a callable object as its first argument
- bind() performs a partial function call
- It "binds" the remaining arguments to this object and returns a new callable

  auto match_cat = bind(match, "cat"); //bind "cat" to match and return
                                       //match_cat

- If we call this, it will call match() and pass "cat" to the call
  match_cat();
  match("cat");

------------------------------
Argument Forwarding
------------------------------
- match_cat() can take arguments
- These are forwarded to match()
    match_cat(arg1, arg2); //could be called as...below
    match(arg1, arg2, "cat");
- They can be mingled with the bound arguments
    match_cat(arg1, arg2); //could be called as... below
    match(arg1, "cat", arg2);

---------------------
Placeholders
---------------------
- We need to say where these arguments will appear
- We do this by using a "placeholder" argument
  * _1 will be replaced by arg1
  * _2 will be replaced by arg2
  * etc
- These are defined in the std::placeholders namespace
  auto match_cat = bind(match, _1, "cat"); //captures "cat" as second argument

  match_cat("dog"); //is called as ...
  match("dog", "cat");

-------------------------
Argument Ordering
-------------------------
- match_cat's arguments can be forwarded in a different order
- To do this, we just change the order of the placeholders

  auto match_cat = bind(match_general, _2, "cat", _1);
  match_cat(arg1, arg2); //is called as...
  match(arg2, "cat", arg1);

-----------------------------------
Lambda equivalent
-----------------------------------
- This is equivalent to a C++14 Lambda which creates a local variable

  auto match_cat = [species="cat"](const string& animal){
      return match_general(animal, species);
  };

  cout << count_if(begin(animal), end(animal), match_cat);

- It takes the animal as argument, and then it calls match_general(), with
  "animal" and bound variable as arguments
- Clearly, Lambda seems to be the better option

-----------------------------
bind1st() and bind2nd()
-----------------------------
- C++98 provided bind1st() and bind2nd()
  * Bind only the 1st or 2nd argument
- These have been superseded by the more flexible bind()
- They were deprecated in C++11 and removed in C++17
*/

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace std::placeholders;

bool match(const string &animal) {
  cout << R"(argument is ")" << animal << R"(")" << "\n";
  return animal == "cat";
}

bool match_general(const string &animal, const string &species) {
  cout << R"(1st argument is ")" << animal << R"(", 2nd argument is )"
       << species << "\"" << "\n ";
  return animal == species;
}
int main() {

  vector<string> animals = {"cat", "dog", "tiger", "lion", "cat", "giraffe"};
  // it will call the match function each time
  auto n = count_if(begin(animals), end(animals), match);
  cout << R"(The vector contains )" << n << R"( occurences of the word "cat")"
       << "\n";

  vector<string> animals1 = {"cat",  "dog", "tiger",  "lion",
                             "bear", "cat", "giraffe"};
  // doesn't compile. This is where std::bind comes handy
  //  auto ns = count_if(begin(animals), end(animals), match("cat"));
  cout << R"( occurences of the word "cat")"
       << "\n";

  cout << "----------------------std::bound--------------------------\n";
  // we pass match_general as the first argument, then the placeholder, then
  // "cat" This will return an object which binds "cat" as the second argument
  // to match_general. And will take one argument, which will be the first
  // argument to match_general()
  auto match_cat = bind(match_general, _1, "cat");
  if (match_cat("dog")) { // calls match_general("dog", "cat")
    cout << "Matched\n";
  } else {
    cout << "Not Matched\n";
  }

  // we can also use this for our algorithm call
  cout << "The vector contains ";
  // animal passed as first argument to match_general
  cout << count_if(begin(animals), end(animals), match_cat);
  cout << R"( occurences of the word "cat")" << "\n";

  cout << "------------with C++14 Lambda with local variable--------\n";

  auto match_cat1 = [species = "cat"](const string &animal) {
    return match_general(animal, species);
  };
  cout << "The vector contains ";
  // animal passed as first argument to match_general
  cout << count_if(begin(animals), end(animals), match_cat1);
  cout << R"( occurences of the word "cat")" << "\n";
}

/*
---------------------------
Member Function Pointers
---------------------------
- We cam define a pointer to a member function of a class
- Their use is more complicated than with function pointers
  * Requires different syntax
  * May need to provide the "this" pointer. Normally compilers will do
    it for you, if you are calling it directly. But if you are going through a
    pointer then you may need to do that yourself.

- Member function pointers cannot be called directly.
 * Must be explicitly dereferenced.

 -------------------------------------
 Defining a Member Function Pointer
 -------------------------------------
 - We can define a pointer to a member function of a class

   class Test{
     ...
     void func(int a, const string& b);
   };

   //Define pfunc as a pointer to a member function of Test
   void(Test::*pfunc) (int, const string&); //we need the extra parentheses

   //make pfunc point to the member function
   pfunc = &Test::func;                     //The '&' is compulsory here

-----------------------------------------
Calling a Member Function Pointer
-----------------------------------------
- To call a member function pointer, we first need an object
- We access the pointer (member function pointer) as a member of the object,
then we dereference it
- To do this, we use .* operator. Both . and *

   Test test;
   (test.*pfunc)(42, "Hello"s);

- There is also a ->* (arrow-star) operator, for pointers to objects

   Test *ptest = &test;
   (ptest->*pfunc)(42, "Hello"s);

---------------------------------------------------
C++11 and Member Function Pointers
---------------------------------------------------
- C++11 features make working with member function pointers much simpler
- We can use "auto" to create the member function pointer
- We can just initalize the pointer with the address, and let the compiler work
out what the type is
  auto pfunc = &Test::do_something;

- We can use a type alias
  using PfuncType = void(Test::*)(int, const string&);
  vector<PfuncType> ptrs;

---------------------------
Callable Objects
---------------------------
- C++11 provides std::mem_fun() in <functional>
- This takes a member function pointer as argument and returns a Callable object
    auto f = mem_fun(pfunc);
- When we invoke this callable object, we need to pass the "this" object as the
first argument
    f(test, 42, "Hello"s); //pass the "this" object as the first argument

----------------------------------
Member Function Pointer and bind()
----------------------------------
- We can also use std::bind() to generate a callable object

    class matcher{
      public:
        bool match(const string& animal, const string& species){
          return animal==species;
        }
    };

    matcher m;
    //capture "cat" as the second argument to matcher::match()
    auto match_cat = bind(&matcher::match, &m, _1, "cat");

- _1 will be the placeholder for the first argument animal

---------------------------------------------
Applications of Member Function Pointers
---------------------------------------------
- Concurrency
  * Needed to run member functions in their own thread. With threads, you have
    to have the code for the thread inside a function, and then create a thread
    object which has the address of the function. If you are writing a class
    which has member functions which run in their own thread, that means you
    need to pass member function pointers as arguments to thread constructor
- Run-time decision making
  * You could have several objects of the same class, and then you decide which
    object has the member function called
- Choose which object is used
  * Use bind() to bind the arguments to a member function call
  * Use a placeholder for the caller to provide the object
- Choose which member function is called
  * Make a contaner of member function pointers
- Use switch statment or if/else to make the decision
  * You could have a container of member funcion pointers, and
then you decide which one of these member functions gets called
- You could use that for implementing state machines, callbacks and so on
*/

#include <functional>
#include <iostream>
#include <string>

using namespace std;

class Test {
public:
  void func(int a, const string &b) {
    cout << "func called with arguments " << a << " and " << b << "\n";
  }
};

namespace mem_fun_ptr_and_bind {
class matcher {
public:
  bool match(const string &animal, const string &species) {
    return animal == species;
  }
};

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
void example() {

  vector<string> animals = {"cat",  "dog", "tiger",  "lion",
                            "bear", "cat", "giraffe"};
  matcher m;
  // capture "cat" as the second argument to matcher::match()
  auto match_cat = bind(&matcher::match, &m, std::placeholders::_1, "cat");

  // pass the callable object to count strings()
  auto n = count_strings(animals, match_cat);
  cout << R"(The vector contains )" << n << R"( occurences of the word "cat")"
       << "\n";
}
} // namespace mem_fun_ptr_and_bind

int main() {

  // define pfunc as a pointer to a member function of Test
  void (Test::*pfunc)(int, const string &); // we need the extra parentheses

  // Make pfunc point to the member function
  pfunc = &Test::func; // The '&' is not optional here

  // C++11
  // auto pfunc = &Test::func;

  cout << "With Test object:\n";
  Test test;
  (test.*pfunc)(42, "Hello"s);

  cout << "\nThrough pointer to Test:\n";
  Test *ptest = &test;
  (ptest->*pfunc)(42, "Hello"s);

  {
    std::cout << "\n-------------use of std::mem_fun-----------------\n";
    // define pfunc as a pointer to a member function of Test
    auto pfunc = &Test::func;

    // generate a callable object from pds
    auto f = mem_fn(pfunc);

    // invoke this callable object
    Test test;
    f(test, 42, "Hello"s); // pass the "this" object as the first argument
  }
  std::cout << "\n----------use member function pointer and bind----------\n";
  mem_fun_ptr_and_bind::example();
}

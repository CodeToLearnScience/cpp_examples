/*-----------------
  Storing Lambdas
 -----------------
 - lambda expressions are mainly used for implementing temporary functions
 - However, lambda expressions are "first class objects". Its an object of the
 functor class that the compiler generates
 - We can store a lambda expression in a variable and pass them to a function.
   //store the lambda function in a variable
   auto is_longer_than = [max](const string& str){return str.size() > max;}

   //pass this variable as the predicate
   auto res = find_if(cbegin(words), cend(words), is_longer_than);
 - the compiler will create an object. We cannot know the type of this object it
 is a class that is defined by the compiler. So we have to use auto, and the
 compiler will provide the name for us. And then we can pass this as a callable
 object, to something like an algorithm call.

 ---------------------------------------
 Returning a Lambda from a Function call
 ---------------------------------------
- Because a lambda expression is a first-class object, we can also return a
lambda expression from a function
  //function which returns a lambda function. We have to use auto for the return
    type. C++14
  auto greeter(const string& salutation){
    return [salutation] (const string& name){return salutation + ", "s + name;};
  }
- This lambda expression will capture the function argument because that is a
variable which is in scope in the function body and then you can do something
inside the boyd of the lambda. The lambda also take an argument itself, i.e., it
will capture this "salutation" argument and then it will append some other
things to it, including arguments
- Calling this function will return a lambda
  //store the lambda function in a variable
  auto greet = greeter("Hello"s);
- This greet that is returned is a lambda expression. It takes someone's name as
argument and it adds a greeting to it.

------------------
Partial evaluation
------------------
- Partial evaluation is a functional programming technique, in which data is
evaluated in stages.
 * e.g., formatting pages in a document viewer. If you open 700 page document
   instead of formatting all 700 pages at once, it will format the pages
   displayed
 * reduces computation
 * can make processing simpler
 * many applications in AI, database queries, scientific computations etc.
- We can use lambda expressions with capture to implement Partial evaluation.
- We have already done that with greeter and greet. That is it processes the
name of the person as it gets it.
- When we call greeter(), it performs a partial evaluation
  * It processes the salutation part of the greeting, but no the name
  * Code which issues a greeting only has to provide the name
  * It doesn't need to process the salutation, or know how it is processed
  * The salutation processing is written once, instead of every time someone is
    greeted
----------------------------
Capture by reference caveats
----------------------------
- Returning a reference to a local variable is dangerous
  int& func(){ //dangling reference
    int x{7};
    return x;
  } //x is destroyed when the function returns
 - A lambda which captures by reference has a reference to the variable
 - If we call the stored lamba after the captured variable has gone out of scope
 we have a "dangling reference" problem
 - When we capture by reference, we must make sure that the captured variable
 is still valid when the lambda is called
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// function which returns a lambda function
auto greeter(const string &salutation) {
  return [salutation](const string &name) { return salutation + ", "s + name; };
}

int main() {
  vector<string> words{"a",    "collection", "of",     "words",
                       "with", "varying",    "lengths"};
  int max{5};

  // save the lambda expression in a variable
  auto is_longer_than = [max](const string &str) { return str.size() > max; };

  // pass this variable as the predicate
  auto res = find_if(cbegin(words), cend(words), is_longer_than);

  // display it
  if (res != cend(words)) {
    cout << R"(The first word which is more than 5 characters long is ")";
    cout << *res << R"(")" << "\n";
  }

  // store the lambda function in a variable
  auto greet = greeter("Hello"s);

  // call the lambda function
  cout << "Greeting: " << greet("students"s) << "\n";
  cout << "Greeting: " << greet("James"s) << "\n";

  auto greet_formal = greeter("Good Morning"s);
  cout << "Formal greeting: " << greet_formal("Dr. Stroustrup"s) << "\n";
}

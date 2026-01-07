/* Lambda Expressions and Capture
 - we can pass data to the lambda expression through the arguments
 - If we have an algorithm call which uses a lambda expression, then we can only
   pass elements of the container. We cannot add more arguments because the
   signature of the lambda expression has to match the expectations of the
   algorithm
 - A lambda expression has access to global or non-local variables, just like a
 regular function
 - It can also access static variables in the same scope
 - Limited access to local variables. This is in the scope where the algorithm
 is being called
 - If we have a local variable, which is a reference and was initialized with a
 const expression, then the lambda expression can read and write those variables
 - If we have a local variable, which is an integer or enumerated type, and was
 initialized with a constant expression, then the lambda expression can read
 those but not modify them

 --------------------------------------
 Lambda Expressions and Local variables
 --------------------------------------
 - If a lambda expression needs full access to local variables, it can "capture"
 them
 - This is done by putting the local variable(s) inside the []
   int n{2};
   [n](int arg){return (n*arg);} //captures the local variable n

   int x{2}, y{3};
   [x,y](int arg){return (x*arg+y);} //captures local variables x and y
------------------------------------
How is Lambda Capture is Implemented
------------------------------------
- A lambda with capture is Implemented as a "functor with state"
  * The functor has a private data member which stores the variable
  * It is initialized in the functor's constructor
  * The data member is available in the operator () body
- By default, the capture variable is passed to the functor's constructor by
  value
  * The functor has its own copy of the captured variable
  * known as "Capture by value"
- By default, the data member is const
  * The function call operator cannot modify its copy of the variable
- Demonstrated using ge_n class
--------------------
Capture by reference
--------------------
- To change a captured variable, we need to capture it by reference
- To do this, we put an & before the captured variable
  int n{2};
  [&n](int arg){return (n*arg);} //captured the local variable n by reference

------------------------------
Lambda capture Implementation
------------------------------
- A lambda with capture by reference is also Implemented as a "functor" with
state
- However, the member variable is a reference to the captured variable
- The captured variable will be passed to the functor constructor by reference
  * Its function call operator can modify the captured variable through the
    reference
  * Its known as "Capture by reference"
- This is Demonstrated using class ge_n_idx class

-----------------
Implicit Capture
-----------------
- We can make a lambda function capture all variables in scope
- This is known as "implcit capture"
  * [=] will capture all variables by value
  * [&] will capture all variables by reference
- Capturing all local variables by reference can make the code difficult to
  maintain
  * The lambda body could modify any variable in scope
- Usually it is safer to capture by reference only those variables which the
lambda function needs to alter
 * [=,&x] will capture x by reference, all others by value
- To make sure that a and b are not altered
 * [&, =a, =b] will capture a and b by value, all others by reference

-------------------------------------
Lambda Functions and Member Functions
-------------------------------------
- It is possible to define a lambda expression inside a member function. This
is different from the algorithm case. In the algorithm the lambda was a callable
object, which we were supplying, and the algorithm function called that directly
- We can just write a lambda expression inside a member function and that is
some local code. We can execute that or we can save it and use it later
  test.do_it()
  //called as Test::do_it(&test);
  //&test is available in the member function body as "this"
- When we have a member function, the member function is always called on some
object and a pointer to that object is passed as the first argument to the
function as shown above. So this is actually an extra argument that you do not
see in the signature
- If we call a member function on an object, then the address of the object is
passed as the first argument and you can access it inside the body of the member
function as a variable called "this". And "this" will be a pointer to Test
- In effect, "this" is a variablein the scope of the member function
- Therefore, when we have a lambda expression inside a member function, it is
allowed to capture "this"
- This allows the lambda expression to access data members and call other member
functions of the class
--------------------
Capturing this
--------------------
- To capture the class object we put [this], [&] or [=]
  * [=this] and [&this] are not allowed
- These all capture the object by reference, even though they should, in some
cases, capture it by value
  class Test{
      int time{0}; //data member
      void countdown(){ //member function which calls a lambda expression
        [this](){
            if(time>0){
                cout << time << endl;
            }
            else if(time==0){
                cout << "Liftoff!" << endl;
            }
            --time;
        }();
      }
  };

- You may think that capturing "this" by reference is a little bit dangerous
because the lambda expression can modify any data member. And in C++17, we also
have the opportunity to capture the object by value
 - In C++17, [*this] captures by value
- That means the lambda expression only has a copy of the object. So the lambda
expression has an immutable copy of the object
- This prevents it from accidentally changing the object

*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

// functor
class ge_n {
public:
  ge_n(const size_t n) : n(n) {}
  bool operator()(const string &str) const { return str.size() > n; }

private:
  const size_t n;
};

// functor for incrementing idx
class ge_n_idx {
public:
  ge_n_idx(const size_t n, int &idx) : n(n), idx(idx) {}
  bool operator()(const string &str) const {
    ++idx;
    return str.size() > n;
  }

private:
  const size_t n; // captured by value
  int &idx;       // captured by reference
};

// example of lambda expression inside a class
class Test {
  int time{10}; // data member

public:
  void countdown() { // member function which calls a lambda expression
    [this]() { // capture class object by reference. *this captures by value
      if (time > 0) {
        cout << time << "\n";
      } else if (time == 0) {
        cout << "Liftoff!" << "\n";
      }
      --time;
    }(); // putting () after lambda expression causes the lambda expression to
    // be executed. So this will make the compiler create an object of the
    // funtor class and call the function call operator in the functor class. So
    // we have actually got two classes; the Test class which we defined and the
    // functor class which compiler will define
  }
};

int main() {
  vector<string> words{"a",    "collection", "of",     "words",
                       "with", "varying",    "lengths"};
  // find the first element with more than 5 characters
  auto res = find_if(cbegin(words), cend(words),
                     [](const string &str) { return str.size() > 5; });

  // display it
  if (res != cend(words)) {
    cout << R"(The first word which is more than 5 characters long is ")";
    cout << *res << R"(")" << "\n";
  }

  // but if we want to return the string with length which is given by n
  // then we can do it by supplying n and capturing it in lambda
  size_t n{3};

  auto res1 = find_if(cbegin(words), cend(words), [n](const string &str) {
    return str.size() > n;
  }); // lambda captures local variable n

  // display it
  if (res1 != cend(words)) {
    cout << R"(The first word which is more than )" << n
         << R"( characters long is ")";
    cout << *res1 << R"(")" << "\n";
  }

  // same example using functor
  auto res2 = find_if(cbegin(words), cend(words), ge_n(n)); // using funtor

  // display it
  if (res2 != cend(words)) {
    cout << R"(The first word which is more than )" << n
         << R"( characters long is ")";
    cout << *res1 << R"(")" << "\n";
  }

  // lets say now we want to be able to find the index of this variable that
  // matches
  // we set idx = -1; because that will be equal to the number of processed
  // elements minus one
  // Without mutable we will get compiler error and the reason for that is that,
  // this will generate a functor which has a const member to represet the index
  // so in the member function, this will increment a const private data number
  // and that is not allowed
  // Adding mutable makes that member non-const and its going to be modifiable
  // object
  // If we don't use &idx we will get -1 as answer the reason is functor has a
  // copy of the captured variable, so when this was being modified in the
  // functor's member function, that was only modifying the copy. It was not
  // doing anything to change this local variable. So when we print this out,
  // this is going to be the local variable which we initialized to -1 so we get
  // -1 and not the copy which the functor made, which disappears when this call
  // returns
  // So by using &idx, this is going to also increment the local variable
  // through the reference
  int idx{-1};
  auto res3 =
      find_if(cbegin(words), cend(words), [n, &idx](const string &str) mutable {
        ++idx;
        return str.size() > n;
      }); // lambda captures local variable n

  // display it
  if (res3 != cend(words)) {
    cout << R"(The first word which is more than )" << n
         << R"( characters long is ")";
    cout << *res3 << R"(")" << "\n";
    cout << "The index is " << idx << "\n";
  }

  // same example using functor
  int funct_idx{-1};
  auto res4 = find_if(cbegin(words), cend(words),
                      ge_n_idx(n, funct_idx)); // using functor

  // display it
  if (res4 != cend(words)) {
    cout << R"(The first word which is more than )" << n
         << R"( characters long is ")";
    cout << *res3 << R"(")" << "\n";
    cout << "The index is " << funct_idx << "\n";
  }

  // lambda inside a class example
  Test test;
  for (int i = 0; i < 12; ++i) {
    test.countdown();
  }
}

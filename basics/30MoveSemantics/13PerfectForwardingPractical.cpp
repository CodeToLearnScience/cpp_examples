/*
-------------------------------
Perfect Forwarding Practical
-------------------------------
- We will write a function that creates objects of this class

  class Test{
    string m_str;

  public:
    Test(const string& str) : m_str(str) {}        //called when lvalue passed
    Test(string&& str) : m_str(std::move(str)){}   //called when rvalue passed
    ...
  };
- This is a very simple version of make_pair(), if you like, or perhaps it
should be make-single!

-------------------------
make_test() function
-------------------------
- The make_test() function will use perfect forwarding to ensure that the move
constructor is called whenever possible
- The function will use a forwarding reference

  template <class T>
  Test make_test(T&& x){
    return Test(std::forward<T>(x));
  }

- It may look as though we are introducing an extra copy operation here, but
modern compilers should be able to optimize this away. And in fact in C++17,
they are required to elide that copy constructor call.

-------------------------------------------------
C++ now has a few more functions which will make objects of library classes like
smart pointers which we will see next
*/

#include <iostream>
#include <string>

using namespace std;

class Test {
  string m_str;

public:
  Test(const string &str) : m_str(str) {
    cout << "const String& constructor called\n";
  }
  Test(const string &&str) : m_str(std::move(str)) {
    cout << "string&& constructor called\n";
  }
};

void g(string &x) { std::cout << "Modifiable version of g called\n"; }

void g(string &&x) { cout << "Move version of g called\n"; }

template <class T> Test make_test(T &&x) {
  // to tell us what type the argument make_test() is
  g(std::forward<T>(x));
  return Test(std::forward<T>(x));
}

int main() {
  string hello{"Hello"};

  cout << "Calling make_test() with lvalue argument\n";
  Test t1 = make_test(hello);
  cout << "\nCalling make_test() with rvalue argument\n";
  Test t2 = make_test(std::move(hello));
  cout << "\n";
}

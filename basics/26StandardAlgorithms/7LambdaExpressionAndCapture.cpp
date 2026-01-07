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
 */

#include <iostream>

using namespace std;

int global{99}; // non-local variable

int main() {             // scope containing the lambda expression
  static int answer{42}; // static variable in containing scope
  const int one{1};      // local variable in containing scope
  const int &r_one{one}; // local variable in containing scope

  []() {                    // start of lambda body
    cout << global << "\n"; // lambda body can access non-local variables
    cout << answer << "\n"; // lambda body can access static variables
    // does not compile with VS
    cout << one << "\n"; // lambda body can read local variables, provided...
    // does not compiel with VS, gcc or clang
    // cout << r_one << "\n"; // lambda body can read local variables,
    // provided...
  }; // end of lambda body
} // end of scope containing the lambda expression

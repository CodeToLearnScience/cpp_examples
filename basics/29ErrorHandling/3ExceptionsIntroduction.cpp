/*
------------------------
std::exception
------------------------
- In C++, you are actually allowed to use any type you want for an exception
object, including built-in types
- C++98 added the std::exception class to the language
- This provides a consistent interface to exceptions
- std::exception is the base class of an inheritance hierarchy. So this is one
of the very few examples of where the library uses inheritance polymorphism.
Generally they avoid it for performance
- It has a number of sub-classes
  * including std::out_of_range
- It has a what() virtual member function
  * This returns a C-style string describing the erorr

------------
Try Block
------------
- The exception mechanism requires some code to manage exceptions at run-time
- This code is added by the compiler, but we need to tell the compiler to
generate it
- To do this, we put code that could throw inside a "try" block

  vector<int> vec;

  try{                            //start of the try block
    cout << vec.at(2) << endl;    //code that may throw an exception
  }                               //End of the try block

-------------------
Catch block
-------------------
- Then for the handler, we have another block with the catch key word in front
of it.
- The type of exception we are going to handle goes in brackets after the catch
keyword
- If we put a base class here, all its sub-classes will be handled as well
- If we put a reference to base, dynamic binding will be used

  //catch block that can handle std::exception and all its sub-classes
  catch(const exception& e){
   cout << e.what() << endl; //code to handle the exception
  }

-------------------------------
Uncaught Exceptions
-------------------------------
- If an exception is not handled by any of the catch blocks after the try block,
the program will try to find one in the "enclosing scope"
  * If the try/catch block is in a function body, it will look for a handler in
    the function
- If it does not find one, it will jump out of the current function and look for
a handler in the function's caller
- If it does still not find one, it jumps to that function's caller, and so on
- If there is no suitable handler, the program terminates after going to main by
keep jumping to function's caller
*/

#include <exception>
#include <iostream>
#include <vector>

using namespace std;

namespace try_catchByRef_example {
void example() {
  vector<int> vec;
  try {
    cout << vec.at(2) << endl; // throws an exception
  } catch (const std::exception
               &e) { // will handle all sub-classes of std::exception
    cout << "Exception caught: " << e.what()
         << endl; // print out a description of the error condition
  }
}
} // namespace try_catchByRef_example

// Static binding will be used
namespace try_catchByVal_example {
void example() {
  vector<int> vec;
  try {
    cout << vec.at(2) << endl; // throws an exception
  } catch (
      const std::exception e) { // will handle all sub-classes of std::exception
    cout << "Exception caught: " << e.what()
         << endl; // print out a description of the error condition
  }
}
} // namespace try_catchByVal_example
int main() {

  vector<int> vec;
  // cout << vec[2] << "\n"; // invalid element access - undefined behaviour,
  // This
  //  will not perform range checking
  // cout << vec.at(2) << "\n"; // Performs range checking
  cout << "Finished\n";

  cout << "\n========Demonstration of try-catch============\n";
  try_catchByRef_example::example();
  // try_catchByVal_example::example();
}

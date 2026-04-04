/*
-----------------------
Catch Statements
-----------------------
- A catch block can only come after a try block
- We can have more than one catch block for the same try block
- If we want to handle exceptions with different static types, we add another
catch block for each type
- The exception will be handled by the first catch block that can handle it

----------------------------------
Multiple Catch and Inheritance
----------------------------------
- Normally we use std::exception hierarchy
- To make this work as expected, we should put the catch blocks in reverse order
  * The most derived class first
  * The base class last

    catch(const out_of_range& e){...} //First block that matches out_of_range
    catch(const exception& e){...}    //Handles all other sub-classes of
                                      //std::exception

-------------------------------
Writing an exception handler
-------------------------------
- The exception handler should take the exception object by reference
- This allows polymorphism to work
  * what() is a virtual member function
- Unless you need to modify the exception object, make it a const reference
- When the program is executing in a catch block, it may not be in a stable
state
  * Avoid allocating memory
  * Avoid creating new variables
  * Avoid calling functions
  * If possible, only use variables of built-in type
- Never do anything that might throwa new exception
- Keep the code simple

-------------------------------
Nested try/catch blocks
-------------------------------
- We can put a try/catch block inside another try block
- If the inner catch block cannot handle the exception, the program will look
for one in the outer catch block

  //outter try block
  try{
    //inner try block
    try{
      catch(const std::bad_alloc&e){...}
    }
    catch(const std::exception& e){...}
  }
-------------------------------------------
Catching exceptions in a different function
-------------------------------------------
- We sometimes want an exception to be handled in a different function from
where it happened

  void get_file(){  //code which could throw an exception
   ...
  }
  void process_data(){
    get_file();
  }
- Here, we want any exceptions from get_file() to be handled in process_data()
- To do this, we leave the exception unhandled in get_file()
- We put the try block and catch block in process_data

   void get_file(){
     ...  //code which could throw an exception
   }
   void process_data(){
     try{
       get_file();
     }
     catch{
       catch(const exception& e){...}
     }
   }
*/

#include <exception>
#include <iostream>
#include <new>
#include <stdexcept>
#include <vector>

using namespace std;
// although std::out_of_range is more specific here, since std::exception
// appears first, that will be executed first. This means, if you have an
// inheritance hierarchy, you need to put the catch handlers upside down
namespace multiple_catch_blocks {
void example() {
  try {
    vector<int> v;
    cout << v.at(2) << "\n"; // may throw an exception of type std::out_of_range
  } catch (const exception &e) { // will handle all sub-classes of
                                 // std::exception
    cout << "std::exception\n";
  } catch (const std::out_of_range
               &e) { // only handles exceptions of type std::out_of_range
    cout << "std::out_of_range\n";
  }
}
} // namespace multiple_catch_blocks

namespace nested_try_catch {
void example() {
  vector<int> vec;
  try {
    try {
      cout << vec.at(2) << "\n"; // throws an exception
    } catch (const std::bad_alloc &e) {
      cout << "Bad alloc catch block\n";
      cout << "Exception caught: " << e.what() << "\n";
    }
  } catch (const std::exception &e) {
    cout << "Std::exception catch block\n";
    cout << "Exception caught: " << e.what() << "\n";
  }
}
} // namespace nested_try_catch

namespace catching_exception_in_different_func {
// function which throws an unhandled exception
void func(const vector<int> &vec) { cout << vec.at(2) << "\n"; }
void example() {
  vector<int> vec;
  // catch any exceptions thrown by func()
  try {
    func(vec);
  } catch (const std::exception &e) { // handle exception
    cout << "std::exception catch block\n";
    cout << "Exception caught: " << e.what() << "\n";
  }
}
} // namespace catching_exception_in_different_func

int main() {
  multiple_catch_blocks::example();
  nested_try_catch::example();
  catching_exception_in_different_func::example();
}

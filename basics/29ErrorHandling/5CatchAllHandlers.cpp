/*
----------------------------------------------------
Catch-all Handlers
----------------------------------------------------
- This can handle an exception of any type
  * Including built-in types, library types and custom classes
try{
  ...   //Code that might throw an exception
}
catch(...){
  cout << "Caught an exception of unknown type\n";
}

------------------------------------
Use of Catch-all Handlers
------------------------------------
- It can be useful to put a catch-all handlers after the other catch blocks
- This will catch any exceptions that have been missed

  try{
    //code that might throw an exception
  }
  catch (const NetworkConnectionError& e){
    //Handler Code
  }
  catch (const DataError& e){
    //handler code
  }
  catch(const std::exception &e){
    cout << "Unhandled std::exception:" << e.what();
  }
  catch(...){cout << "Unhandled exception\n";}

- It can also be useful to put a catch-all handler inside main()
  * If the handler is executed, we will know the program terminated due to an
    uncaught exception and not some other bug
  * This will tell us that there are missing catch blocks, or error conditions
    which do not anticipate

    int main(){
      try{
        ...
      }
      catch(...) {cout << "Unhandled exception\n";}
    }

-------------------------------------
Pros and Cons of Catch-all Handlers
-------------------------------------
- A catch-all handler is useful when testing
- However, it is not helpful when debugging
  * Allowing the debugger to trap the exception instead will give more useful
    information
- No information about the error condition
  * THe exception type is not available in the handler
- Does not capture other events
  * Unix signals
  * Windows "Structured exceptions"

*/

#include <iostream>
#include <vector>

using namespace std;

namespace catch_all_handlers {
void example() {
  try {
    throw 43;
    // throw "something went wrong";
    /* vector<int> vec;
     cout << vec.at(2) << "\n";
     */
  } catch (...) {
    cout << "Caught an exception of unkown type\n";
  }
}
} // namespace catch_all_handlers

int main() { catch_all_handlers::example(); }

/*
---------------------------
Exception Throwing
---------------------------
- When an exception is thrown, several things happen
- The thrown object is copied into a special area of memory
- This area is set up by the compiler
  * it is accessible by any catch block which can handle the object type
- Every local variable in scope is destroyed
  * Including the original copy of the thrown object
- The program immediately leaves the scope
  * It does not execute any further instructions in the scope

-------------------------------
Stack unwinding
-------------------------------
- The program will look for a catch block that can handle the exception
- If it cannot find one, it will immediately destroy all local variables and
exit the current scope
- It then looks in the enclosing scope
- This continues until it finds a suitable handler
  * If it reaches main() withoug finding one, the program calls std::terminate()
- This process of repeatedly destroying local variables and exiting the current
scope is known as "stack unwinding"

--------------------------------------
Rethrowing an Exception
--------------------------------------
- When a suitable handler is found, the program executes the code in it and
continues
- Normally, it will proceed to the next instruction after the try/catch block
and continue executing from there
- However, the handler can "rethrow" the exception
- In this case, the exception will be handled again, but in a handler belonging
to another try/catch block
- To rethrow the same exception object, use throw with no argument
  * If we give an argument, it will throw a copy of that object
- Since the exception is thrown outside the current try block, the program will
regard this as a completely new exception
- A fresh process of stack unwinding begins

-------------------------------------------
Applications of Rethrowing
-------------------------------------------
- Rethrowing exceptions can be used to
  * Log the exception at the point where it happens
  * Add extra information to the exception
  * Convert the exception to a higher level type

  catch (TcpHandshakeFailure& e){ //Handler for low-level networking exception
    logger << e.what() << "\n";   //Log the details of the error condition
    e.remote_host = remote_host;  //Save the name of the server in the exception
    //throw NetworkConnectionError(e); //Rethrow high-level exception to UI
    throw;                             //Rethrows original exception object
  }

*/

#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

namespace rethrow_example {

void func(const vector<int> &vec) {
  try {
    cout << vec.at(2) << "\n";
  } catch (const std::out_of_range &e) {
    cout << "Abandoning operation due to exception\n";
    cout << "Exception caught: " << e.what() << "\n";
    // throw std::exception(e);
    throw; // rethrow exception
  }
}

void exaple() {
  vector<int> vec;
  try {
    func(vec);
  } catch (const std::exception &e) {
    cout << "Call to fun failed\n";
    cout << "Exception caught: " << e.what() << "\n";
  }
}

} // namespace rethrow_example

int main() { rethrow_example::exaple(); }

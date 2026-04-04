/*
------------------------------------
std::exception Subclasses
------------------------------------
- bad_alloc
  * Thrown when a memory allocation fails
- bad_cast
  * Thrown when a dynamic_cast fails
- logic_error
  * Parent class for error conditions resulting from faulty logic
- runtime_error
  * Parent class for error conditions beyond the program's control

--------------------------------------------
Subclasses of std::logic_error
--------------------------------------------
- out_of_range
  * Attempting to access an element outside a defined range
  * e.g. vector::at()
- invalid_argument
  * The argument to a function is not acceptable
  * e.g. passing a non-numeric arguments to stoi()
- domain_error
  * The argument to a function is outside the domain of applicable values
  * e.g. valid date field
- length_error
  * The lenth limit of an object is exceeded
  * e.g. appending too many elements to a string

-----------------------------------------
Subclasses of std::runtime_error
-----------------------------------------
- overflow_error
  * The result of a computation is too large for the result variable
- underflow_error
  * The result of a floating-point computation is too small for the result
variable
- range_error
  * An internal computation gives a value which cannot be represented by the
result variable

---------------------------------------------------
C++ Standard Library and Exceptions
---------------------------------------------------
- Surprisingly, the Standard Library makes little use of exceptions
- sqrt() does not throw std::domain_error when given -1 as an argument
  //code that "should" throw std::domain_error error
  sqrt(-a) //returns "nan"
- Instead, it returns the value NaN ("not a number")
- C++ streams do not throw exceptions by default
- The programmer can usually deal with error conditions by checking the stream
- Exceptions can be optionally enabled, but the resulting code is usually more
complex

  //Enable exceptions for ifile
  ifile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  //Throws an exception if text.txt cannot be opened for reading
  ifile.open("text.txt");

- The reason why the C++ Standard Library make little use of exceptions is
efficiency
  * Checking for exceptions and handling them requires extra code
  * In some applications, this overhead may not be acceptable
- However, these exceptions are used in third-party libraries
- We can also use them in our code

---------------------------------------------
Exceptions and Special Member Functions
---------------------------------------------
-----------------------------
Destructors and Exceptions
-----------------------------
- When an exception is thrown, the destructor is called for all local variables
in the current scope
- What happens if destructor throws an exception
  * If the exception is handled by a catch block in the destructor, this is safe
  * If the exception is not handled by the destructor, a stack unwind will ensue
  * If another exception is being processed, there could be two stack unwind
    operations in progress at the same time
  * C++ implementations assume there is only one active exception at a time
  * Undefined behavior
- Destructors should never throw exceptions
- If code in a destructor does throw, it must be handled by the destructor
- Usually this is not a problem, as destructors should only release resources

------------------------------------
Constructors and Exceptions
------------------------------------
- If an unhandled exception is thrown during a constructor call, the
partially-initialized object will be destroyed
  * All its data memebers will also be destroyed
  * If the object is a child class, its parent part will be destroyed as well
- As far as the rest of the programis concerned, an object does not exist until
its constructor has successfully completed
- An exception in a constructor should be left for the caller to handle
  * THe caller will then know the object has not been successfully created
- The constructor should only handle the exception if it can solve the problem
and continue initializing the object
- If we allow the caller to handle the exception, there are only two possible
outcomes from calling a constructor
  * Either no exception and a successfully created object
  * Or an exception is thrown and there is no objec

----------------------------------------
Constructors that Throw Exceptions
----------------------------------------
- Constructors can also throw exceptions to report errors to the caller
  * THis is useful, because constructors do not have a return value
  * This is one of the advantages that exceptions have over error codes
*/

#include <cmath>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

namespace enable_exception {
void example() {
  ifstream ifile;

  // Enable exceptions for ifile
  ifile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    // throws an exception if text.txt cannot be opened for reading
    ifile.open("text.txt");
  } catch (const std::exception &e) {
    cout << "exception caught: " << e.what() << "\n";
  }
}
} // namespace enable_exception

namespace constructors_with_exceptions {

class StudentGrade {
  int grade;

public:
  StudentGrade(int grade) : grade(grade) {
    if (grade < 10 || grade > 100) {
      // Invalid grade - throw exception
      throw std::out_of_range("Invalid grade");
    }
  }
};

void example() {

  int result;
  cout << "Please enter the student's grade (between 0 and 100)" << "\n";
  cin >> result;
  try {
    StudentGrade sgrade(result);
    cout << "Sgrade created\n"; // if we get here, no exception was thrown
                                // - safe to use sgrade
  } catch (const std::out_of_range &e) {
    cout << "StudentGrade constructor threw an exception: " << e.what() << "\n";
  }
}

} // namespace constructors_with_exceptions

int main() {
  try {
    cout << sqrt(-1) << "\n";
  } catch (const std::exception &e) {
    cout << e.what() << "\n";
  }
  enable_exception::example();
  constructors_with_exceptions::example();
}

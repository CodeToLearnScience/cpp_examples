/*
----------------------------------
Custom Exception Class
----------------------------------
- We can write our own exception class
- Usually it is best to derive it from one of the subclasses of std::exception
  * Existing interface
  * We can inherit code instead of rewriting it
  * Will be caught by std::exception handlers
- We do not derive directly from std::exception
  * std::exception has a default constructor only
  * No provison for passing a custom error message

--------------------------------------------
Custom Exception Class Requirements
--------------------------------------------
- A custom exception class needs constructors which take a string
  * Both std::string and C-style
- It needs a copy constructor
  * This can be inherited or defaulted
- It can override the what() virtual member function
  * If extra functionality is required
- It can have data members to store information relevant to the error condition
  * Recommendation: only use built-in types

-------------------------------------------
Custom Exception Class Considerations
-------------------------------------------
- A custom exception object will be copied into memory off the local stack
- The program may be in an unstable state
- The object should be lightweight
  * Have the minimum number of data members
  * Perform minimal processing
- In particular, it should not do anything that might throw a fresh exception

----------------------------------------
Custom Exception Class Example
----------------------------------------
- We will create an exception class for our student grades program
- We will call our class invalid_student_grade
- This should be thrown when the user enters a grade which is negative or
greater than 100%
- This error condition represents a value which is outside its defined range
  * We will derive our class from std::out_of_range

---------------------------------
invalid_student_grade constructor
---------------------------------
- std::out_of_range has constructor which takes strings
- We need to implement these for consistency

  invalid_student_grade(const char* s) : std::out_of_range(s) {}
  invalid_student_grade(const string& s) : std::out_of_range(s) {}

- We also implement a default constructor
- This calls the out_of_range constructor with a suitable error string
    invalid_student_grade() :
      std::out_of_range("Invalid grade : please try again"){}

------------------------------------------------------------
invalid_student_grade Members
------------------------------------------------------------
- The only relevant data is the error string
- This is sorted in the std::out_of_range part of the class
  * We do not need any data members of our own
- Since we do not have any data members, we do not need to implement a copy
constructor
- In this case the compiler will generate a copy constructor which will copy
the std::out_of_range part of the class
- For similar reasons, we do not need to define a destructor
- We could also override the virtual what() member function
  * Not actually needed here
- This is declared const, because it does not change the exception object
- It is also declared noexcept, because it does not throw Exceptions
- It returns the error string, as const char*
  const char* what() const noexcept override{...}
*/

#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

namespace custom_exception_class {
class bad_student_grade : public std::out_of_range {
public:
  // Default constructor
  bad_student_grade() : std::out_of_range("Invalid grade: please try again") {}

  // We need constructors which take a string, for consistency with
  // std::exception
  bad_student_grade(const char *s) : std::out_of_range(s) {}
  bad_student_grade(const string &s) : std::out_of_range(s) {}

  // These default operators are good enough as we do not have any data members
  bad_student_grade(const bad_student_grade &other) = default;
  bad_student_grade &operator=(const bad_student_grade &other) = default;

  // Finally, we can override the virtual what() member function
  // const cha* what() const noexcept override {/* ... */}
};

class StudentGrade {
  int grade;

public:
  StudentGrade(int grade) : grade(grade) {
    if (grade < 0) {
      throw bad_student_grade("bad grade");
    }
    if (grade > 100) {
      throw bad_student_grade();
    }
  }
};

void example() {
  int result;
  cout << "Please enter the student's grade (between 0 and 100)" << "\n";
  cin >> result;
  try {
    StudentGrade sgrade(result);
    // if we get here, no exception was thrown - safe to use sgrade
    cout << "Valid student grade entered: " << result << endl;
  } catch (bad_student_grade &e) {
    cout << e.what() << "\n";
  }
}
} // namespace custom_exception_class

int main() { custom_exception_class::example(); }

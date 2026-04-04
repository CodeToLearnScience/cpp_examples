/*
----------------------------------
std::exception Hierarchy
----------------------------------
- C++ defines an std::exception class
- This is the base class for an inheritance Hierarchy
  * Consistent interface for exception object
  * Enables polymorphism - reduces the number of handlers needed

------------------------------------
Logic and Runtime Errors
------------------------------------
- A logic error represents something that is under the control of the programmer
  * e.g. violating precondition
- A logic error could be prevented by the programmer
  * e.g. checking function arguments before processing them
- A runtime error represent something that is beyond the programmer's direct
control
  * e.g. running out of memory

-----------------------------------------------
std::exception Hierarchy Interface
-----------------------------------------------
- std::exception defines five public member functions
  * constructor
  * copy constructor
  * assignment operator
  * virtual member function what()
  * virtual destructor
- what() returns a C-style string
- what() cannot throw an exception

-----------------------------------------------------
std::exception Hierarchy Constructor
-----------------------------------------------------
- exception, bad_alloc and bad_cast have a default constructor
- The others do not have a default constructor, but have a constructor that
takes a string argument
  * This string can be either a C-style string or a std::string
  * It will be returned when what() is called
  * It should give information about the error condition

*/

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

namespace example1 {

int at(const vector<int> &vec, int pos) {
  // check index corresponds to a valid element
  // if not, throw std::out_of_range with a suitable error message
  if (vec.size() < pos + 1) {
    string str{"No element at index "s + to_string(pos)};
    throw std::out_of_range(str);
  }

  // return the element
  return vec[pos];
}
void example() {

  vector<int> vec;
  // vector<int> vec{1, 2, 3};

  try {
    int el = at(vec, 2);
    cout << "vec[2] = " << el << endl;
  } catch (const std::exception
               &e) { // will handle all subsclasses of std::exception
    cout << "Exception caught: " << e.what() << endl;
  }
}
} // namespace example1

int main() { example1::example(); }

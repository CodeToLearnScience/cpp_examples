// we will implement String class with RAII idiom for managing resources
/* - In the string class the "resource" is the memory allocation
   - The string class is responsible for managing the lifetime of this resource

       * It must make sure the resource is correctly acquired before being used
       * It must  make sure the resource is correctly released when it is no
           longer needed
       * It must make sure that any copying of the resource is handled correctly
       * It must make sure that any transfer of the resource to another object
        of this class is handled correctly.

*/
// With Synthesized copy constructor (default compiler generated) program would
// crash because, it has just copied the data pointers. So the pointer in the
// argument object has overwritten the pointer in the new object. So they both
// have the same pointers So we have two objects pointing to the same memory. So
// when their destructors call delete, the arguments to delete is the same
// pointer. So we are trying to release the same memory twice. Hence double
// free. So that means second time we are releasing memory that does not belong
// to us. This is also called shallow copy, where we were just copying the
// pointer addresses
//
// So we need to do deep copy
//
// Same problem will be there when we use Synthesized assignment operator, which
// does shallow copy
/*
 Deep assignment is bit more complex than the copy constructor
 - We need to provide the target object with its own memory allocation. Before
   that we need to release the old allocation, because that is the last time
   we have access to the address of that memory
 - This must be large enough to hold the data
    * delete [] data;
    * data = new char[size];
 - Before that, we need to check for self-assignment
    * If "this" and "arg" are the same object, they use the same memory-pointer
    * If this->data is deleted, arg->data will be deleted as well
    * We will not be able to access the characters in arg->data
 - If the objects are the same, we do not modify them. That is they point to
   same pointer in C++.
*/

/*
 Rule of Three
 - If a class needs to implement one of
    * Copy constructor
    * Assignment operator
    * Destructor
 - Then it probably needs to implement the other two as well
    * e.g. class with pointer member allocated with "new" in constructor and
      release by "delete" destructor
    * copy constructor is needed to perform deep copy when copying
    * Assignment operator is needed to perform deep copy on assignment
 - This is called "Rule of Three"
 - The default constructor is not included in the Rule of Three as we usually
   need to implement a constructor anyway
* Sometimes, it is useful to provide a default constructor which initializes
  the object as "empty"
 */

/* Rule of Zero
  - Which says if the compiler Synthesized special member functions gives
  correct behavior then you don't need to implement
  */

#include <iostream>
#include <string>

using namespace std;

class String {
  char *data; // Array member to store the characters
  int size;   // The number of elements in the array.

public:
  // constructor
  String(const std::string &s) : size(s.size()) {
    data = new char[size]; // allocate the heap memory for the data

    // populate the data
    for (int i = 0; i < size; ++i) {
      data[i] = s[i];
    }
  }
  // Synthesized member functions
  // String(const String& arg) : size(arg.size), data(arg.data){}
  // String& operator=(const String& arg) {size=arg.size; data=arg.data; return
  // *this;}

  String(const String &arg) : size(arg.size) {
    cout << "Calling copy constructor\n";
    data = new char[size];           // Allocate the heap memory
    for (int i = 0; i < size; ++i) { // popualate the memory with arg's data
      data[i] = arg.data[i];
    }
  }

  // Assignment operator
  String &operator=(const String &arg) {
    cout << "Calling assignment operator\n";
    if (&arg != this) { // check for self-assignment
      delete[] data;
      data = new char[arg.size];
      size = arg.size;
      for (int i = 0; i < size; ++i) { // popualate the memory with arg's data
        data[i] = arg.data[i];
      }
      return *this;
    }
  }

  // Destructor
  ~String() {
    cout << "Calling destructor" << "\n";
    delete[] data; // release the heap memory
  }

  int length() { return size; }
};

int main() {
  String str("1"s);
  String str2("Two"s);
  String str3(str2); // With default compiler generated copy constructor,
                     // program will crash
  cout << "Str2 size: " << str2.length() << "\n";
  cout << "Str3 size: " << str3.length() << "\n";
  str2 = str3; // with default compiler generated assignment operator, program
               // will crash
  cout << "Str2 size: " << str2.length() << "\n";
  cout << "Str size: " << str.length() << "\n";
}

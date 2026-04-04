/*
--------------------------
Exception-Safe Class
--------------------------
- Consider our RAII class
  class String{
  private:
    int size;
    char* data;
    ...
  };

- Is this class Exception-Safe?
- We will review the special member functions

------------------
Constructor
------------------
- The Constructor allocates the memory used by the "data" member

  String(const char* str, int size) : size(size){
    data = new char[size];
    //Any other code needed to configure the new object
  }

- The Constructor cannot be noexcept
- The Constructor provides the strong exeception guarantee
  * No objects are created or modified when there is an error condition
  * The function will return immediately, without allocating a value to "data"
  * The partially-created object will be destroyed.

------------------
Copy Constructor
------------------
- The copy constructor allocates memory for "data" member
- It then copies the characters from its argument

   String (const String& arg){
     size = arg.size;
     data = new char[size];

     //Any other code neeeded to configure the new object
     for(int i=0; i<size; ++i){
       data[i] = arg.data[i];
     }
   }

- Like the class constructor, it provides the strong exeception guarantee

-----------------
Destructor
-----------------
- The destructor releases the memory used by the "data" member

  ~String() noexcept{
    //any other code needed to clean up the object
    delete [] data;
  }
- The destructor provides the no-throw guarantee
  * delete and delete[] are defined as noexcept

-------------------
Assignment Operator
-------------------
- The assignment operator performs a "deep copy"
- This releases the memory for "data" and then reallocates it
- The only operation that could throw is new
  * The function will return immediately, without allocating a new value to
    "data"
  * The target object will be unmodified
  * The assignment operator provides the strong exception guarantee

--------------------------
Exception Safety and RAII
--------------------------
- With RAII, the constructor and copy constructor automatically provide the
strong exception guarantee
- The destructor automatically provides the no-throw guarantee
- The assignment operator, if implemented carefully, also offers the strong
guarantee
*/

#include <iostream>
#include <utility>

using namespace std;

class String {
private:
  int size;
  char *data;

public:
  String(int size) : size(size), data(new char[size]) {}
  String(const String &arg) : size(arg.size) {
    cout << "Calling copy constructor\n";
    data = new char[size]; // Allocate the heap memory for arg's data
    for (int i = 0; i < size; ++i) {
      data[i] = arg.data[i]; // Populate the memory with arg's data
    }
  }

  // Assignment operator
  // There is a problem with this implementation: We call delete before we call
  // new. If new throws an exception, then data will have the previous value
  // that's now pointing to the memory which is no longer valid
  /*String &operator=(const String &arg) {
    cout << "Calling assignment operator\n";
    if (&arg != this) { // check for self-assignment
      cout << "Reallocating memory\n";
      delete[] data;             // Release the original memory
      data = new char[arg.size]; // Allocate data member
      size = arg.size;           // Assign to the size member
      for (int i = 0; i < size; ++i) {
        data[i] = arg.data[i];
      }
    }
    return *this; // return the assigned-to object
  }*/

  // So correct implementation of assignment operator
  // this is all exception-safe
  // Downside is that, for brief moment we are using twice the memory
  String &operator=(const String &arg) {
    cout << "Calling assignment operator\n";
    if (&arg != this) { // check for self-assignment
      cout << "Reallocating memory\n";
      char *ndata = new char[arg.size]; // allocate the data member
      delete[] data;                    // Release the original memory
      data = ndata;                     // Allocate data member
      size = arg.size;                  // Assign to the size member
      for (int i = 0; i < size; ++i) {
        data[i] = arg.data[i];
      }
    }
    return *this; // return the assigned-to object
  }

  // destructor
  ~String() {
    cout << "Calling destructor: " << static_cast<void *>(data) << "\n";
    delete[] data; // release the heap memory for the data
  }

  // declare overloaded swap() as a friend of this class
  friend void swap(String &l, String &r) noexcept;

  void print() {
    cout << "String with size = " << size;
    cout << ", data address " << static_cast<void *>(data) << "\n";
  }
};

inline void swap(String &l, String &r) noexcept {
  cout << "\nIn String::swap\n";
  swap(l.size, r.size);
  swap(l.data, r.data);
}

int main() {
  String a(5), b(6);
  cout << "Before swapping\n";
  cout << "a: ";
  a.print();
  cout << "b: ";
  b.print();

  swap(a, b);

  cout << "\n" << "After swapping\n";
  cout << "a: ";
  a.print();
  cout << "b: ";
  b.print();
  cout << "\n";
}

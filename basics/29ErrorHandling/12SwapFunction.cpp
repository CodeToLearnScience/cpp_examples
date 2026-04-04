/*
--------------------
std::swap() Function
--------------------
- The C++ library provides an std::swap function
- This exchanges the data in its arguments
  swap(s1, s2); //s2 will have s1's old data and vice versa
- std::swap() is declared noexcept
  * It offers the no-throw guarantee

------------------------
Overloads of std::swap()
------------------------
- std::swap() is a generic function
- It copies its arguments
- There are overloads for library types which take advantage of thier internal
structure
- e.g. the std::string overload swaps the string's internal data buffers
  //pseudo-code
    char *temp = s1.ptr; //pointer initialization
    s1.ptr = s2.ptr;     //pointer assignment
    s2.ptr = temp;       //pointer assignment

- Some algorithms need to swap elements internally
  * e.g sort()
- They call the non-member swap() function
- The call will be made to the generic std::swap() which uses copying
  * Unless there is an overload for the element's type

------------------------
Should we Overload swap?
------------------------
- When we write a class, we can overload swap() for that class
- This is worth doing if
  * The class is expensive to copy
  * and its objects could be swapped, e.g. by sorting container

----------------------------
Implementing swap
----------------------------
- Algorithms assume that swap() is fast and does not throw exceptions
- Our swap() will need access to data members
  * Either make it a friend, or delegate to a member function
- We write the code inline so that the compiler can optimize away the function
call
- We make it noexcept
- We call swap() for each data member
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
  String &operator=(const String &arg) {
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

  // if we comment our implementation of swap from class, the default library
  // swap will be called that will call copy constructor and assignmen operator
  // as follows
  // That will be slow. That's why we need our own swap()
  /*
   Before swapping
   a: String with size = 5, data address 0x1e0fb2b0
   b: String with size = 6, data address 0x1e0fb2d0
   Calling copy constructor
   Calling assignment operator
   Reallocating memory
   Calling assignment operator
   Reallocating memory
   Calling destructor: 0x1e0fb700

   After swapping
   a: String with size = 6, data address 0x1e0fb2b0
   b: String with size = 5, data address 0x1e0fb2d0

   Calling destructor: 0x1e0fb2d0
   Calling destructor: 0x1e0fb2b0
   */
}

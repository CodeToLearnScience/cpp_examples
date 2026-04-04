/*
-----------------
Copy and Swap
-----------------
- Alternative approach to writing an assignment operator
  * Create a local variable which is a copy of the argument
  * Swap the contents of the local variable with the "this" object
  * Return the "this" object, which now contains the correct values
  * The local variable is then destroyed

----------------------
Create and Initialize
----------------------
- To create a new object and initialize it with the values we want, we use the
copy constructor

  String& operator=(const String& arg){
    String temp(arg); //create copy of argument object
  }

- If this throws
  * The "temp" object is destroyed
  * The function returns immediately
  * "this" is unmodified
  * The exception is left for the caller to handle

---------------------
Swap the Objects
---------------------
- "temp" now contains the required values
- To get these values into "this" we use std::swap

  String& operator=(const Strin& arg){
    String temp(arg);     //create a copy of argument object
    swap(*this, temp);    //Replace our data with temp's data
  }

- The swap operation is noexcept (cannot throw)
- "this" now contains the required values
- "temp" contains the original values

------------------------
Return the New object
------------------------
- Finally, we return the assigned-to object

  String& operator=(const String& arg){
    String temp(arg);   //create copy of argument object
    swap(*this, temp);  //Replace our data with temp's data
    return *this;       //Return the assigned-to object
  } //temp is destroyed as destructor is called

- When the function returns, the destructor for "temp" is called
- This releases the original memory allocation
  * No memory leak

------------------------------------------
Assignment Operator with Strong Guarantee
------------------------------------------
- This is known as the "copy-and-swap" idiom
- Advantages
  * No need to check for self-assignment ("temp" and "this" are distinct
    Objects)
  * Code reuse - does not duplicate code from copy constructor and destructor
  * Much shorter code with less scope for errors
- Disadvantages
  * Always makes a new allocation, even if the target object already has enough
    memory
  * Creates an extra object, which increases memory consumption

-------------------------------------
Copy-and-Swap and Exception Guarantee
-------------------------------------
- Copy-and-Swap provides the strong exception guarantee
- If an exception occurs while initializing the new object, we do not swap
  * We destroy the new object
  * The original object is unmodified
- The program is in the same state as when the assignment operation began
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
    String temp(arg);  // create copy of other
    swap(*this, temp); // Replace our data with temp's object
    return *this;      // return the assigned-to object
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
  String a{5};
  cout << "a: ";
  a.print();

  String b{6};
  cout << "b: ";
  b.print();
  cout << "\n";
  cout << "copy construction of c from b\n";
  String c{b};

  cout << "b: ";
  b.print();
  cout << "c: ";
  c.print();
  cout << "\n";
  cout << "Assigning a from c\n";
  a = c;

  cout << "a: ";
  a.print();
  cout << "c: ";
  c.print();
  cout << "\n";
  cout << "Exiting program...\n";
}

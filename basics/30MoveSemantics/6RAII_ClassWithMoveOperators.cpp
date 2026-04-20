/*

---------------------------------
RAII Class with Move Operators
---------------------------------
- We need to add a move constructor and move assignment operator to our RAII
class.

  class String{
    private:
      int size;
      char *data;

    public:
      ... //Member functions

  };

- So this is the string-like class that we have been building up, throught this
course. It allocates memory in the constructor, and releases memory in the
destructor, which is the RAII idiom.

--------------------------------
Move constructor (first attempt)
--------------------------------
- Out move constructor needs to move the data members of the argument object
- As these are built-in types, we can just copy them

  //move constructor
  String(String&& arg) noexcept{
    data = arg.data;
    size = arg.size;
    cout < " Move constructor called\n";
    //anything else?
  }

- We know that with shallow copy, we ended up with two objects which have the
same value for the pointer and when the objects get destroyed, the pointer is
deleted twice. And this is really what is happening here.
What we are trying to achieve here with move constructor? When we move from this
argument object, we are actually moving from the arguments members into these
members. That is arg.size to size and arg.data to data. So after that operation,
these members are going to be invalid so lets do something about it. If we have
an invalid pointer, then we can express that by saying it is equal to the null
pointer. So we need to modify as follows


  //move constructor
  String(String&& arg) noexcept{
    data = arg.data;
    size = arg.size;
    cout < " Move constructor called\n";
    //anything else?
    arg.data = nullptr;
    arg.size = 0;
  }

- We also need to make sure that the final value of this argument can be deleted
safely. Here that's not a problem as deleting null pointer has no effect

--------------------------------------------
Move Assignment Operator
--------------------------------------------
- We can write a move assignment operator which is similar to the traditional
copy assignment operator

 //Move assignment operator
 String& operator=(String&& arg){
   if(this!=&arg){
     delete[] data;
     data = arg.data;
     size = arg.size;
     cout << "Move assignment operator called\n":

     arg.data = nullptr;
     arg.size = 0;
   }
   return *this;
 }

- Alternatively, we can use "move-and-swap"

  //move assignment operator
  String& operator=(string && arg)noexcept{
    String temp(std::move(arg)); //call move operator. When the destructor is
                                 //called this temporary object is destroyed,
                                 //that will release the memory
    swap(*this, temp);           //exchange our data with temp's data
    return *this;
  }
- This is similar to the copy-and-swap idiom, except it uses the move
constructor to create the temporary object
  * "this" has the pointer from "arg"
  * "temp" has the orignal pointer from "this", which is deleted
  * "arg" has a null pointer
*/

#include <iostream>

using namespace std;

namespace move_constructor_example {

class String {
private:
  int size;
  char *data;

public:
  String(int size) : size(size), data(new char[size]) {}

  String(const String &arg) {
    cout << "Calling copy constructor\n";
    size = arg.size;
    data = new char[size]; // allocate the heap memory for arg's data

    for (int i = 0; i < size; i++) { // populate the memory with arg's data
      data[i] = arg.data[i];
    }
  }

  // assignment operator
  String &operator=(const String &arg) {

    cout << "Calling assignment operator\n";
    if (&arg != this) {
      cout << "Reallocating memory\n";
      delete[] data;             // release the orignal memory
      data = new char[arg.size]; // allocate the data member

      size = arg.size; // assign to the size member

      for (int i = 0; i < size; i++) { // populate the memory with arg's data
        data[i] = arg.data[i];
      }
    }
    return *this;
  }

  // Move constructor
  String(String &&arg) noexcept {
    cout << "Calling move constructor\n";
    data = arg.data;
    size = arg.size;
    // anything else
    arg.data = nullptr;
    arg.size = 0;
  }

  // Move assignment operator
  /*String &operator=(String &&arg) {
    if (this != &arg) {
      delete[] data;
      data = arg.data;
      size = arg.size;
      cout << "Move assignment operator called\n";

      arg.data = nullptr;
      arg.size = 0;
    }
    return *this;
  }*/

  // Move assignment operator using swap. The output will be bit different
  // compared to above implementation. We will have the move constructor call
  // for the initialization of the temporary object and then we have the
  // destructor call whent the temporary object is destroyed
  String &operator=(String &&arg) {
    cout << "Move assignment operator called\n";
    String temp = std::move(arg); // Call move constructor
    swap(*this, temp);            // Exchane our data with temp's data
    return *this;
  }
  // Destructor
  ~String() {
    cout << "Calling destructor: " << static_cast<void *>(data) << "\n";
    delete[] data;
  }

  friend void swap(String &l, String &r) noexcept;

  void print() {
    cout << "String with size " << size;
    cout << ", data address " << static_cast<void *>(data) << "\n";
  }
};

inline void swap(String &l, String &r) noexcept {
  using std::swap;
  swap(l.size, r.size);
  swap(l.data, r.data);
}

void example() {
  String a{5};
  cout << "a: ";
  a.print();
  {
    String b{6};
    cout << "b: ";
    b.print();
    cout << "\n";
    cout << "Copy construction of c from b\n";
    String c{b};
    cout << "b: ";
    b.print();
    cout << "c: ";
    c.print();
    cout << "\n";
    cout << "Move construction of d from b\n";
    String d{std::move(b)};
    cout << "b: ";
    b.print();
    cout << "d: ";
    d.print();
    cout << "\n";
  }
}

void example_move_assignment() {
  String a{5};
  cout << "a: ";
  a.print();
  {
    String b{6};
    cout << "b: ";
    b.print();
    cout << "\n";
    cout << "Copy assignment of b from a\n";
    b = a;
    cout << "b: ";
    b.print();
    cout << "a: ";
    a.print();
    cout << "\n";
    cout << "Copy construction of c from b\n";
    String c{b};
    cout << "b: ";
    b.print();
    cout << "c: ";
    c.print();
    cout << "\n";
    cout << "Move assignment of c from a\n";
    c = std::move(a);
    cout << "a: ";
    a.print();
    cout << "c: ";
    c.print();
    cout << "\n";
  }
}
} // namespace move_constructor_example

int main() {
  move_constructor_example::example();
  cout << "============Move assignment example================\n";
  move_constructor_example::example_move_assignment();
}

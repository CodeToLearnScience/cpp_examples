/*
---------------------------
Reference Counting
---------------------------
- Reference counting is a technique for allowing different objects to share the
same resource (usually of the same class)
- An integer is used to store the number of objects which are sharing the
resource
- This is known as a "reference counter"
  * Initially, the counter is 0 when no objects are sharing resource
  * When an object is bound to resource, the counter is incremented
  * When an object unbound, the counter is decremented
  * When there are no remaining bound objects, the counter is 0
  * The resource is now unbound

-------------------------------
Reference Counted String
-------------------------------
- We will add reference counting to our String class
- We need an integer to store the count
- This must be visible to all the objects which bind to the shared memory. So
the usual way to do that is to allocate integer on the heap
- The class will have a member which is a pointer to this integer

  class String{
  private:
    int size;
    char* data;    //The shared memory - all
    int* counter;  //The reference counter

    public:

  };

----------------
Constructor
----------------
- The Constructor allocates the counter as well as allocating memory
- Initially, this has the value 0, as there are no objects bound
- We acquire the resource by allocating the shared memory
- We increment the counter, because there is now a bound object

  String(int size) : size(size){
    counter = new int{0};  //allocate the counter - no bound object Initially
    data = new char[size]; //acquire the resource

    //any other code needed to configure the new object
    ++(*counter); //"this" has been bound - increment the counter
  }

--------------------
Destructor
--------------------
- When an object is destroyed, it is no longer bound to the shared memory
- We therefore decrement the counter
- If the counter is non-zero, there are still bound objects
  * We must not release the memory as it is still shared
- If the counter is 0, "this" is the only remaining bound object
  * We can (and should) release the memory as it is no longer shared

  ~String() noexcept{
     --(*counter) ; //An object has been unbound - decrement the counter

     if(*counter == 0){
       delete counter; //we are the last bound object - release the memory
       delete[] data;
     }
  }

-------------------------
Copy Constructor
-------------------------
- When we copy-construct an object, the new object should have the same value as
the argument

  String s2(s1);

- s1 and s2 will share the same memory allocation and same counter. So now we
have an another object which is bound to this memory
  * Their pointers will have the same value
  * A shallow copy is good enough
- The reference counter needs to be incremented because we now have another
object bound to shared memory
  * A new object is bound to the shared memory

  String(const String& arg){
    //make a shallow copy of the argument
    size = arg.size;
    data = arg.data;
    counter = arg.counter;

    ++(*counter); //"this" has been bound - increment the counter
  }

------------------------------
Assignment Operator
------------------------------
- Assignment operator is bit more compliated
- For assignment, we can also do a shallow copy and increment the counter
  s2 = s1;
- If s1 and s2 are bound to the same shared memory, this is sufficient
- If s1 abd s2 are bound to different shared memory, first we must unbind s2
from its memory
  * Decrement s2's counter
  * If this brings s2's counter down to zero, we must release s2's shared memory
- So this is another example of the copy constructed logic consisting of the
destructor's logic, followed by the constructo's logic.
- Check for self-assignment before incrementing counter. Otherwise we will have
counter off by one

  String& Operator=(const String& arg){
    if(data!=arg.data){  //if arg is bound to different shared memory
      --(*counter);      //unbind from our current shared memory
      if(*counter==0){
        delete counter;
        delete[] data;
      }
      //make a shallow copy of the assignment
      size = arg.size;
      ++(*counter);     //"this" has been bound - increment the counter
    }
    return *this;       //return the assigned
  }

--------------------------------------------------
Assignment Operator with copy-and-swap
--------------------------------------------------
- Alternatively, we can use copy-and-swap

  String& operator=(const String& arg){
     String temp(arg);     //create copy of other
     swap(*this, temp);    //Replace our data with temp's data
     return *this;         //Return the assigned-to object
  }                        //temp is destroyed

- We need to add the counter member to swap()
    inline void swap(String& l, String& r) noexcept{
      using std::swap;
      swap(l.size, r.size);
      swap(l.data, r.data);
      swap(l.counter, r.counter);
    }

----------------------------
Move Operators
----------------------------
- The existing operators are almost sufficient
- For the move constructor
  * Add a shallow copy of the counter pointer
  * Set the moved-from object's counter to null as well as the data pointer
  * Modify the rest of the code to check the counter before dereferencing it
- We do not increment the counter
  * A move operation does not change the number of bound objects
  * It just transfers the binding from one object to another
*/

#include <iostream>

using namespace std;

namespace reference_counting {

class String {
private:
  int size;
  char *data;
  int *counter; // The reference counter - also allocated on the heap
public:
  String(int size) : size(size) {
    counter = new int{0}; // Allocate the counter - no bound objects initially
    data = new char[size];

    ++*counter; // "this" has been bound - increment the counter
  }
  ~String() noexcept {
    cout << "Destructor: data = " << (void *)data << ", counter = " << counter
         << ", count = " << *counter << endl;
    // Any other code needed to clean up the object
    --*counter;          // An object has been unbound - decrement the counter
    if (*counter == 0) { // If we are the last bound object, release the memory
      cout << "Deleting shared memory at " << static_cast<void *>(data) << endl;
      delete counter;
      delete[] data;
    }
  }

  // Declare overloaded swap() as a friend of this class
  friend void swap(String &l, String &r) noexcept;

  String(const String &arg) {
    // Make a shallow copy of the argument
    size = arg.size;
    data = arg.data;
    counter = arg.counter;

    // Any other code needed to configure the new object
    ++*counter; // "this" has been bound - increment the counter
  }

  String &operator=(const String &arg) {
    cout << "Assigned-to object: data = " << (void *)data
         << ", counter = " << counter << ", count = " << *counter << endl;
    if (data != arg.data) { // If arg is bound to different shared memory
      --*counter;           // Unbind from our current shared memory
      if (*counter ==
          0) { // If we are the last bound object, release the memory
        cout << "Deleting shared memory at " << static_cast<void *>(data)
             << endl;
        cout << "Deleting counter at " << static_cast<void *>(counter) << endl;
        delete counter;
        delete[] data;
      }

      size = arg.size;
      data = arg.data;
      counter = arg.counter;

      ++*counter; // "this" has been bound - increment the counter
    }

    return *this; // Return the assigned-to object
  }

  /*
  // Assignment operator
  String& operator =(const String& arg) {
          cout << "Assigned-to object: data = " << (void*)data << ", counter = "
  << counter << ", count = " << *counter << endl; String temp(arg); // Create
  copy of other swap(*this, temp);                          // Replace our data
  with temp's data return *this;                               // Return the
  assigned-to object } // temp is destroyed
  */

  int length() { return size; }
  int count() { return *counter; }

  friend void swap(String &l, String &r) noexcept;

  void print() {
    cout << "size = " << size;
    cout << ", data address " << static_cast<void *>(data);
    cout << ", counter " << static_cast<void *>(counter);
    if (counter)
      cout << ", count = " << *counter;
    cout << endl;
  }
};

inline void swap(String &l, String &r) noexcept {
  using std::swap;
  swap(l.size, r.size);
  swap(l.data, r.data);
  swap(l.counter, r.counter);
}

void example() {
  String a{5};
  cout << "a: ";
  a.print();

  String b{6};
  cout << "b: ";
  b.print();
  cout << endl;
  cout << "Copy construction of c from b\n";
  String c{b};

  cout << "b: ";
  b.print();
  cout << "c: ";
  c.print();
  cout << endl;
  cout << "Assigning a from c\n";
  a = c;

  cout << "a: ";
  a.print();
  cout << "c: ";
  c.print();
  cout << endl;
  cout << "Exiting program...\n";
}
} // namespace reference_counting

namespace reference_counting_with_move_ops {
class String {
private:
  int size;
  char *data;
  int *counter; // The reference counter - also allocated on the heap
public:
  String(int size) : size(size) {
    counter = new int{0}; // Allocate the counter - no bound objects initially
    data = new char[size];

    ++*counter; // "this" has been bound - increment the counter
    cout << "Constructor: data = " << static_cast<void *>(data)
         << ", counter = " << counter << ", count = " << *counter << endl;
  }
  ~String() noexcept {
    cout << "Destructor: data = " << (void *)data << ", counter = " << counter;
    if (counter) {
      cout << ", count = " << *counter << endl;
      // Any other code needed to clean up the object
      --*counter; // An object has been unbound - decrement the counter
      if (*counter ==
          0) { // If we are the last bound object, release the memory
        cout << "Deleting shared memory at " << static_cast<void *>(data)
             << endl;
        cout << "Deleting counter at " << static_cast<void *>(counter) << endl;
        delete counter;
        delete[] data;
      }
    } else
      cout << endl;
  }

  // Declare overloaded swap() as a friend of this class
  friend void swap(String &l, String &r) noexcept;

  String(const String &arg) {
    // Make a shallow copy of the argument
    size = arg.size;
    data = arg.data;
    counter = arg.counter;

    // Any other code needed to configure the new object
    ++*counter; // "this" has been bound - increment the counter
    cout << "Copy constructor: data = " << static_cast<void *>(data)
         << ", counter = " << counter << ", count = " << *counter << endl;
  }

  String &operator=(const String &arg) {
    cout << "Assigned-to object: data = " << (void *)data
         << ", counter = " << counter << ", count = " << *counter << endl;
    if (data != arg.data) { // If arg is bound to different shared memory
      --*counter;           // Unbind from our current shared memory
      if (*counter ==
          0) { // If we are the last bound object, release the memory
        cout << "Deleting shared memory at " << static_cast<void *>(data)
             << endl;
        delete counter;
        delete[] data;
      }

      size = arg.size;
      data = arg.data;
      counter = arg.counter;

      ++*counter; // "this" has been bound - increment the counter
    }

    return *this; // Return the assigned-to object
  }

  // Move constructor
  String(String &&arg) noexcept {
    cout << "Move constructor called" << endl;
    data = arg.data;
    size = arg.size;
    counter = arg.counter; // Shallow copy of counter pointer

    // Prevent double deletion
    arg.data = nullptr;
    arg.counter = nullptr;
  }
  // Move assignment operator
  String &operator=(String &&arg) noexcept {
    cout << "Move assignment operator called" << endl;
    String temp(std::move(arg)); // Call move constructor
    swap(*this, temp);           // Exchange our data with temp's data

    return *this;
  }
  int length() { return size; }
  int count() { return *counter; }

  friend void swap(String &l, String &r) noexcept;

  void print() {
    cout << "size = " << size;
    cout << ", data address " << static_cast<void *>(data);
    cout << ", counter " << static_cast<void *>(counter);
    if (counter)
      cout << ", count = " << *counter;
    cout << endl;
  }
};

inline void swap(String &l, String &r) noexcept {
  using std::swap;
  swap(l.size, r.size);
  swap(l.data, r.data);
  swap(l.counter, r.counter);
}

void example() {

  String a{5};
  cout << "a: ";
  a.print();

  String b{6};
  cout << "b: ";
  b.print();
  cout << "\n";
  cout << "Move construction of c from b\n";
  String c{std::move(b)};

  cout << "b: ";
  b.print();
  cout << "c: ";
  c.print();
  cout << "\n";
  cout << "Move assigning a from c\n";
  a = std::move(c);

  cout << "a: ";
  a.print();
  cout << "c: ";
  c.print();
  cout << "\n";
  cout << "Exiting program...\n";
}

} // namespace reference_counting_with_move_ops

int main() {
  reference_counting::example();
  cout << "---------------Reference counting with Move operators-----------\n";
  reference_counting_with_move_ops::example();
}

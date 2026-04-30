/*
----------------------
Unique Pointer
----------------------
---------------------
std::unique_ptr
---------------------
- In most situations, unique_ptr is the best replacement for traditional
pointers which manage heap memory
  * Allocate heap memory in its constructor and has sole ownership of it
  * Automatically releases the memory when it goes out of scope
  * This allows heap-allocated memory to be used like a stack object
- It has the usual advantages of smart pointers
  * The programmer does not need to manage the memory
  * The pointer to the memory cannot be overwritten or invalidated
  * No issues with "shallow copying"
- unique_ptr is very lightweight
  * A unique_ptr object has not more overhead than a traditional pointer
- unique_ptr is defined in <memory>
- unique_ptr is a template class with a traditional pointer as member
- The public member functions of the class implement some of the operations on
traditional pointers, but not all of the operations that you can perform
- Its template parameter is the type of the pointed-to data

   unique_ptr<int> p; //unique pointer that has a pointer to int member

- unique_ptr is a move-only class
  * Moving a unique_ptr transfers the allocated memory from one object to
    another. So that transfers the ownership of the memory

-----------------------------------
unique_ptr initialization in C++11
-----------------------------------
- In C++11, we have to provide the pointer by calling new() explicitly

  //allocate a single int with value 42
   unique_ptr<int> p1{new int(42)}; //p1's member points to the int on the heap

- We can also create a fixed-size array
  //allocate array of 6 ints
  unique_ptr<int []> p2{new int[6]}; //p2s's member points to the first element

  //usually better to use std::array or std::vector
  std::array<int, 6> arr;
  std::vector<int> arr(6);
- The only situation where you would want to use this is if you need a
fixed-size vector on the heap, because the library array cannot be allocated on
the heap, and a vector does not have fixed-size.
- C++14 has make_unique which calls new() internally

  auto p1{make_unique<int>(43)}; //p1's member points to the int on the heap

  auto p2{make_unique<int []>(6)} //p2's member points to the first element
- make_unique() uses perfect forwards its arguments to the constructor

--------------------------------
unique_ptr as Function Argument
--------------------------------
- We can pass unique_ptr objects to functions, using pass-by-move

  void func(unique_ptr<Point> upp){
    cout << upp->x << ", " << upp->y << endl;
  }

  auto ptr{make_unique<Point>(p)};
  func(std::move(ptr)); //cast to rvalue

------------------------------------
Returning unique_ptr from Function
------------------------------------
- We can also return unique_ptr objects from functions
- The object is moved into the function's return space
- This transfers ownership of the allocated memory
- The object is then moved again, into a variable in the caller

   unique_ptr<Point> point_ptr(int x, int y){
     Point p{x,y};                      //Create Point object
     auto ptr{make_unique<Point>(p)};   //Create local unique_ptr object
     return ptr;                        //The allocated memory is transferred
                                        //from p to the returned object
   }

   auto upp {point_ptr(3,6)};
- By the way we don't have to cast return ptr to rvalue here, because the
compiler will always move a return value if it is possible
*/

#include <cstddef>
#include <iostream>
#include <memory>

using namespace std;

namespace unique_ptr_ex {
// data structure representing a point on the screen
struct Point {
  int x;
  int y;
};

void example() {

  // create a unique_ptr to a point which has initial value {3, 6}
  // we are using auto becuase that's good place to use it because, we have a
  // unique_ptr to a Point structure, so we do not need to spell it out
  auto p{make_unique<Point>(Point{3, 6})}; // C++14
  // unique_ptr<Point> p{new Point{3,6}}; //C++11
  cout << p->x << ", " << p->y << "\n";
}

void func(unique_ptr<Point> upp) { cout << upp->x << ", " << upp->y << "\n"; }

void unique_ptr_as_func_arg_ex() {

  // create a unique_ptr to a point which has initial value {3, 6}
  auto p{make_unique<Point>(Point{3, 6})}; // C++14
  // unique_ptr<Point> p{new Point{3,6}}; //C++11
  func(std::move(p));
  // cout << p->x << "\n"; //Error deferencing moved object
}

unique_ptr<Point> point_ptr(int x, int y) {
  Point p = {x, y};
  auto ptr{make_unique<Point>(p)};
  return ptr; // if you put move here, that can confuse the compiler, and it
              // will generate code which is less optimized than if you left it
              // alone
  // return make_unique<Point>(p); // we can also directly return it
}

void return_unique_ptr_from_func_ex() {
  auto res{point_ptr(3, 5)};
  cout << res->x << ", " << res->y << "\n";
}

} // namespace unique_ptr_ex
int main() {

  // In C++11, we have to provide the pointer by calling new() explicitly
  // Allocate a single int with value 42
  unique_ptr<int> p1{new int(42)};
  // allocate array of 6 ints
  unique_ptr<int[]> p2{
      new int[6]}; // p2's member points to the first element of the array

  // C++14 has make_unique, which calls new() internally

  auto p3{make_unique<int>(42)};
  auto p4{make_unique<int[]>(6)};

  // so we can perform most of the operations on a unique_ptr that we can on a
  // traditional pointer
  cout << *p1 << "\n"; // single object can be deferenced
  // cout << p1[0] << "\n"; // Error - single object cannot be indexed
  cout << p2[0] << "\n"; // Array can be indexed
  //  cout << *p2 << "\n":   // Error - array cannot be deferenced
  //  ++p1; //Error - pointer arithmetic not supported
  //  ++p2; //Error - pointer arithmetic not supported
  //  p1 = p2; //Error - unique_ptr can only be moved
  //  unique_ptr<int> p5(p4); //Error - unique_ptr can only be moved
  unique_ptr<int> p5(std::move(p3)); // OK
  //  unique_ptr<int> p6(std::move(p4)); // Error incomatible types
  p1 = nullptr; // calls delete on the pointer member and sets the pointer to
                // nullptr

  unique_ptr_ex::example();
  unique_ptr_ex::unique_ptr_as_func_arg_ex();
  unique_ptr_ex::return_unique_ptr_from_func_ex();
}

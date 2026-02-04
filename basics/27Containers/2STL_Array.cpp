/*
-------------
STL Array
-------------

------------------
Built-in array
------------------
- C++ has a built-in array inherited from C
  int arr[] = {1,2,3,4,5};
- Built-in arrays are faster than std::vector and they are directly compatible
with code written in C
- It has serious disadvantages, including
  * No direct way to find the number of elements
  * Silent conversion to pointer
    - In particular, if you pass an array as an argument to a function, or
      return it from a function call, then it will be converted to a pointer
  * Passing arrays to and from functions requies a size argument
  * Arrays cannot be assinged to each other
- Modern C++ provides std::array which overcomes the above

 ----------------
 std::array
 ----------------
 - std::array is defined in <array>
 - It is a templated type
   * We need to give the type of the element and the number of elements when
     we create an object
   * The parameters are the element type and the number of elements
   * The number of elements is part of the type of the object
   * Trying to use an array with the wrong number of elements gives a compiler
     error
- It has a similar interface to STL containers, while retaining the speed of
  built-in arrays
   * Does not automatically "decay" to a pointer
   * Retains information about its size
   * Supports iterators

---------------------------
std::array object creation
---------------------------
- An std::array object can only be created on the stack
  * The number of elements must be known at compile time
- A contiguous block of memory is allocated to store the elements
- Unlike other containers, the default constructor creates a fully-sized object.
  The elements are default-initialized

------------------------
std::array interface
------------------------
- std::array has a similar interface to std::vector
- size()        //returns number of elements
- empty()       //returns whether array is empty
- operator[]    //Access element by index
- at()          //access element by index with bounds checking
- front()       //access the first element
- back()        //access the last element
- data()        //Returns in built-in array
*/

#include <array>
#include <iostream>

using namespace std;

// function that takes built-in array as pointer to int
// n is the number of elements in the array
void somefunc(int *pi, int n) {
  for (int i = 0; i < n; ++i) {
    cout << pi[i] << ", ";
  }
  cout << "\n";
}

// function that takes std::array of 5 elements
void somefunc(array<int, 5> arr) {
  for (auto el : arr) {
    cout << el << ", ";
  }
  cout << "\n";
}

int main() {

  // std::array can be list-initialized
  std::array<int, 5> arr{1, 2, 3, 4, 5};

  // elements can be accessed and assinged to using indexing
  cout << "arr[3] = " << arr[3] << "\n";

  arr[2] = 6;
  cout << "After assignment arr[2] = " << arr[2] << "\n";

  cout << "Iterator loop: ";
  for (auto it = begin(arr); it != end(arr); ++it) {
    cout << *it << ", ";
  }
  cout << "\n";

  cout << "Range loops: ";
  for (auto el : arr) {
    cout << el << ", ";
  }
  cout << "\n";

  cout << "Indexed loop: ";
  for (size_t i = 0; i < arr.size(); ++i) {
    cout << arr[i] << ", ";
  }
  cout << "\n";

  // array of the same type and size can be assigned
  std::array<int, 5> five_ints;
  five_ints = arr;
  cout << "Elements of five ints: ";
  for (auto el : five_ints) {
    cout << el << ", ";
  }
  cout << "\n";

  // built-in array
  cout << "Built-in array\n";
  int b_arr[] = {1, 2, 3, 4, 5};
  int n = sizeof(b_arr) / sizeof(b_arr[0]);
  somefunc(b_arr, n);

  cout << "std::arry\n";
  somefunc(arr);
}

/* -----------------------
 Reordering Algorithms
-----------------------
- A reordering algorithm re-arranges the elements inside an iterator range
- It does not change thier values
-----------
reverse()
-----------
- reverse() takes the elements in an iterator range and reverses thier order
  reverse(begin(vec), end(vec));
- There is also a _copy() version
  reverse_copy(cbegin(vec), cend(vec), back_inserter(vec3));

---------
rotate()
---------
- rotate() performs a rotation about a given element
- ALl the elements before the pivot are moved to the back of the range
- The pivot and all the elements behind it are moved to the front of the
iterator range

if 1 2 3 4 5 and pivot is 3 then the result will be 3 4 5 1 2
- The pivot will be moved front and the elements are pivot are moved immediatelt
after pivot and the elements before pivot are moved last
- rotate() takes three arguments
  - The beginning of the range
  - An iterator to the pivot element
  - The end of the range
- The return value is an iterator to the original first element
  auto pivot = begin(vec);
  advance(pivot, 2); //use the third element as the pivot
  auto res = rotate(begin(vec), pivot, end(vec));
  //res is an iterator to the element with value 1
-------------
rotate_copy()
-------------
- rotate_copy() writes the result to a destination
- The return value is an iterator to the last plus one element written to the
destination
  auto pivot = begin(vec);
  advance(pivot,2); //use the third element as the pivot

  //perform the rotation
  auto res = rotate_copy(begin(vec), pivot, end(vec), begin(dest_vec));
  //res is an iterator to the element in dest_vec with value 2
*/

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

void print(const vector<int> &vec) {
  for (auto v : vec) {
    cout << v << " ";
  }
  cout << "\n";
}

int main() {

  vector<int> vec1{3, 1, 4, 1, 5, 9};
  cout << "Original vec: ";
  print(vec1);

  vector<int> vec2;

  // make a copy of original vector for use in loop later
  copy(cbegin(vec1), cend(vec1), back_inserter(vec2));
  reverse(begin(vec1), end(vec1));
  cout << "Result of reverse: ";
  print(vec1);

  // use a loop to reverse the elements
  // works irrespective of whether the number of elements is odd or even
  size_t len{vec2.size() - 1};
  for (size_t i = 0; i <= len / 2; ++i) {
    /*
     int temp{vec2[i]};
     vec2[i]=vec2[len-i];
     vec2[len-i]=temp;
     */
    swap(vec2[i], vec2[len - i]);
  }

  cout << "Result of loop reversal: ";
  print(vec2);
  //----------------------------------------------------------------------------
  // rotate()
  cout << "==========demonstration of rotate() algorithm=============\n";

  vector<int> vec3{1, 2, 3, 4, 5};
  cout << "Initial vector: ";
  print(vec3);

  // use the third element as the pivot
  auto pivot = begin(vec3);
  advance(pivot, 2);

  // perform the rotation
  auto res = rotate(begin(vec3), pivot, end(vec3));
  cout << "Result of rotate: ";
  print(vec3);

  // res is an iterator to the element with value 1
  cout << "The original first element was " << *res << "\n";

  //----------------------------------------------------------------------------
  // rotate_copy()
  cout << "==========demonstration of rotate_copy() algorithm=============\n";
  vector<int> vec4(vec3.size());

  // use the third element as the pivot
  auto pivot1 = begin(vec3);
  advance(pivot1, 2);
  auto res1 = rotate_copy(begin(vec3), pivot1, end(vec3), begin(vec4));

  cout << "Result of rotate: ";
  print(vec4);

  // res is an iterator to the element in vec2 with value 3
  cout << "Last element copied was " << *(res1 - 1) << "\n";
}

/* -------
 replace()
 ---------
- replace() changes all elements with a given value to another value

-----------
replace_if()
-----------
- replace_if() changes all elements for which a predicate returns true

----------------------------
_copy() version of algorithm
----------------------------
- Algorithms which change the elements have two versions
- The base version which overwrites the data in the original range
- A_copy() version which writes the data to a different iterator range
  * This is useful when the data neeeds to be preserved for later use
  * Useful for working with associative container
-------------
replace_copy()
- replace() has a_copy version
- replce_copy() writes the data to a destination, instead of overwriting the
orginal data

-----------------
replace_copy_if()
-----------------
- replace_if() has a copy version
- if the predicate returns true, the element will have a different value in the
target container
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void print_vec(const vector<int> &vec) {
  for (auto v : vec) {
    cout << v << " ";
  }
  cout << "\n";
}

int main() {
  // replace all occurences of 1 with 2
  vector<int> vec{3, 1, 4, 1, 5, 9};

  cout << "vec: ";
  print_vec(vec);

  // replace 1 with 2
  replace(begin(vec), end(vec), 1, 2);

  cout << "Vector after replace: ";
  print_vec(vec);

  // equivalent loop
  vector<int> vec2{3, 1, 4, 1, 5, 9};

  for (auto &v : vec2) {
    if (v == 1) {
      v = 2;
    }
  }

  cout << "Vector after loop: ";
  print_vec(vec2);
  //---------------------------------------------------------------------------
  // replace_if()
  vector<int> vec3{3, 1, 4, 1, 5, 9};
  replace_if(begin(vec3), end(vec3), [](int n) { return (n % 2 == 0); }, 6);

  cout << "Vector after replace_if: ";
  print_vec(vec3);

  vector<int> vec4{3, 1, 4, 1, 5, 9};
  for (auto &v : vec4) {
    if (v % 2 == 0) {
      v = 6;
    }
  }

  cout << "Vector after loop: ";
  print_vec(vec4);
  //---------------------------------------------------------------------------
  // replace_copy()

  cout << "repace_copy example: ";
  vector<int> vec5{3, 1, 4, 1, 5, 9};
  cout << "vec5: ";
  print_vec(vec5);

  vector<int> vec6;
  // replace all occurences of 1 with 2
  replace_copy(cbegin(vec5), cend(vec5), back_inserter(vec6), 1, 2);

  cout << "Result of replace_copy: ";
  print_vec(vec6);

  vector<int> vec7;
  for (auto v : vec5) {
    if (v == 1) {
      vec7.push_back(2);
    } else {
      vec7.push_back(v);
    }
  }
  cout << "Result of loop: ";
  print_vec(vec7);
  //---------------------------------------------------------------------------
  // replace_copy_if()
  vector<int> vec8{3, 1, 4, 1, 5, 9};
  cout << "replace_copy_if example: ";
  print_vec(vec8);

  vector<int> vec9;

  // replace all even numbers by 6
  replace_copy_if(
      cbegin(vec8), cend(vec8), back_inserter(vec9),
      [](int n) { return (n % 2 == 0); }, 6);

  cout << "Result of replace_copy_if: ";
  print_vec(vec9);

  vector<int> vec10;
  for (auto v : vec8) {
    if (v % 2 == 0) {
      vec10.push_back(6);
    } else {

      vec10.push_back(v);
    }
  }
  cout << "Result of loop: ";
  print_vec(vec10);
}

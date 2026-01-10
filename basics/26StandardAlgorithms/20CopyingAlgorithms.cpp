/*
 ---------------------
 - Copying algorithms
 ---------------------
 - Copying algorithms copy elements into another range
 - These are often used to populate sequential containers

 -------
 copy()
 -------
 - copy() is the most basic copying algorithm
   vector<int> vec{3,1,4,5,8};
   vector<int> vec2(vec.size()); //the target container must be big enough
   copy(cbegin(vec), cend(vec), begin(vec2));
- We can use back_insert_iterator to populate an empty vector
   vector<int> vec3;
   copy(cbegin(vec), cend(vec), back_insert(vec3));
- This is equivalent to using loop
   vector<int> vec4;
   for(auto v: vec){
     vec4.push_back(v);
   }
-------
copy_n()
-------
- copy_n() will copy only the first n elements of a range

---------
copy_if()
---------
- copy_if() copies only the elements for which a predicate is true
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

  vector<int> vec{3, 1, 4, 1, 5, 9};
  cout << "vec: ";
  print_vec(vec);

  vector<int> vec2(vec.size());
  copy(cbegin(vec), cend(vec), begin(vec2));

  cout << "vec2 After copying: \n";
  print_vec(vec2);

  // use an insert iterator to populate an empty container
  vector<int> vec3;
  copy(cbegin(vec), cend(vec), back_inserter(vec3));
  cout << "vec3 After copying from back_inserter: \n";
  print_vec(vec3);

  // use a loop to populate
  vector<int> vec4;
  for (auto v : vec3) {
    vec4.push_back(v);
  }

  cout << "vec4 After copying from range for loop: \n";
  print_vec(vec4);
  //---------------------------------------------------------------------------
  // copy_n()
  vector<int> vec5;
  copy_n(cbegin(vec), 2, back_inserter(vec5));
  cout << "vec5 After copying first elements of vec to vec5 using copy_n: \n";
  print_vec(vec5);

  //---------------------------------------------------------------------------
  // copy_if()
  vector<int> vec6;
  copy_if(cbegin(vec), cend(vec), back_inserter(vec6),
          [](int n) { return n % 2 == 1; });
  cout << "vec6 After copying odd elements of vec to vec6 using copy_if() and "
          "lambda predicate: \n";
  print_vec(vec6);
}

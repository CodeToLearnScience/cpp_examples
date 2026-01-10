/* --------------------
 Merging algorithms
 --------------------
- merge() combines two sorted iterator ranges into a destination
- The destination will contain all the elements from both ranges, in order
- In set theory, this is the "sum" of the ranges
  merge(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2),
    back_inserter(vec3));
- By deafault, the < operator is used to order the elements of vec3
-------------------
set_intersection()
-------------------
- set_intersection() combines two sorted iterator ranges into a destination
- The destination will contain only the elements which are present in both
ranges, in order
- in set theory, this is the "intersetcion" of the ranges
  set_intersection(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2),
    back_inserter(vec3));
- By deafault, the < operator is used to order the elements of vec3

------------------
set_union()
------------------
- set_union() combines two sorted iterator ranges into a destination
- The destination will contain elements which are in either range, in order
- Elements which are in both ranges will appear only once
  set_union(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2),
    back_inserter(vec3));
- By deafault, the < operator is used to order the elements of vec3
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
  vector<int> vec2{3, 1, 4, 2, 8};

  sort(begin(vec1), end(vec1));
  cout << "vec1: ";
  print(vec1);

  sort(begin(vec2), end(vec2));
  cout << "vec2: ";
  print(vec2);

  vector<int> vec3;
  merge(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2),
        back_inserter(vec3));
  cout << "Result of merging vec1 and vec2: ";
  print(vec3);

  //---------------------------------------------------------------------------
  // set_intersection()
  cout << "===========demonstration of set_intersection()==============\n";
  vector<int> vec4;
  set_intersection(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2),
                   back_inserter(vec4));
  cout << "intersetcion vec1 and vec2: ";
  print(vec4);

  //---------------------------------------------------------------------------
  // set_union()
  cout << "===========demonstration of set_union()==============\n";
  vector<int> vec5;
  set_union(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2),
            back_inserter(vec5));
  // 1 would appear twice because 1 appears twice in vec1. So we can have
  // duplicates which are in one container. And duplicate is ignored once
  cout << "intersetcion vec1 and vec2: ";
  print(vec5);
}

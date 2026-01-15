/*
------------------------
Permutations
------------------------
- If we have a set of every possible arrangement of some elements, this gives
the Permutations of the elements
- For example, all the different ways of group of people can be seated at dinner
- e.g. the Permutations of "abc" are, in alphabetical order
  abc, acb, bac, bca, cab, cba
- There are STL algorithm functions to find the next and previous Permutations
in the sequece

------------------
next_permutation()
------------------
- next_permutation() takes an iterator range
- It reorders the elements to give the next Permutation in ascending order
- e.g. the next Permutation of "abc" is "acd"
- It returns a bool, depending on whether there is next Permutation
- If the elements are sorted in ascending order, calling next_permutation() in a
loop gives all the Permutations
  //loop to print out all Permutations of "abc" in order
  string str{"abc"};
  do{
    std::cout << str << "\n";
  }while(next_permutation(begin(str), end(str));
- This uses the < operator by default, but we can supply a predicate

-------------------
prev_permutation()
-------------------
- prev_permutation() reorders the elements to give the previous permutation
- To get all the permutation in reverse, the elements must be sorted in
descending order

sort(begin(str), end(str), [](int m, int n){return m>n;});
  do{
    std::cout << str << "\n";
  }while(next_permutation(begin(str), end(str));

- This uses the < operator by default, but we can supply a predicate

-------------------
is_permutation()
-------------------
- is_permutation() takes two iterator ranges
- It returns true if both ranges contain the same elements, even if they are in
different order

  //do vec and vec2 contain the same elements"
  if(is_permutation(cbegin(vec), cend(vec), cbegin(vec2), cend(vec2))){
     cout << "vec is a permutation of vec2\n";
  }

- This uses == operator by default, but we can supply a predicate
*/

#include <algorithm>
#include <iostream>
#include <ratio>
#include <string>
#include <vector>

using namespace std;

int main() {
  string str{"abc"};
  cout << "The Permutations of " << str << "\n";

  // loop to print out all th Permutations of str, in order
  do {
    std::cout << str << "\n";
  } while (next_permutation(begin(str), end(str)));

  string str1{"abc"};
  cout << "The permutation of " << str1 << " in reverse order are: " << "\n";

  sort(begin(str1), end(str1), [](int m, int n) { return m > n; });
  do {
    std::cout << str1 << "\n";
  } while (prev_permutation(begin(str1), end(str1)));

  //----------------------------------------------------------------------------
  // is_permutation()
  cout
      << "+++++++++++++demonstration of is_permutation()++++++++++++++++++++\n";
  vector<int> vec{3, 1, 4, 1, 5, 9};
  vector<int> vec2{1, 3, 4, 5, 9, 1};
  cout << "vec: ";
  for (auto v : vec) {
    cout << v << " ";
  }
  cout << "\n";
  cout << "vec1: ";
  for (auto v : vec2) {
    cout << v << " ";
  }
  cout << "\n";
  // do vec and vec2 contain the same elements"
  if (is_permutation(cbegin(vec), cend(vec), cbegin(vec2), cend(vec2))) {
    cout << "vec is a permutation of vec2\n";
  } else {
    cout << "vec is not a permutation of vec2\n";
  }
}

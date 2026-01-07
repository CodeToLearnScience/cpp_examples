/*
 -------------------
 Numeric Algorithms
 -------------------
 - The Standard Library also defines some algorithms in <numeric>
 - These are used for numerical processing of container elements
 - But there are a few in the numeric header

--------
iota()
--------
- iota() populates an iterator range with values which successively increase
by 1
- It takes the iterator range and a string value
  * It assigns this starting value to the first element in the range
  * iota() then increments the value and asigns it to the next element
- These can't be const iterators as it modifies the elements

- Which is equivalent to
  int n{1};
  for(auto &v: vec){
    v=n;
    ++n;
  }

------------
accumulate()
------------
- accumulate() returns the sum of all the elements in an iterator range
- The third argument is the initial value of the sum
- usually this is 0

--------------------------------
accumulate() with extra argument
--------------------------------
- By default, the operator + is used to perform the addition
- To perform a different operation, we can pass a callable object as an
additionla fourth argument
- We can use a lambda function for the extra argument

-----------------------------------------
std::accumulate() and parallel processing
-----------------------------------------
- std::accumulate() is specified to execute sequentially
- The execution is performed as for vector<int> vec{1,2,3}
  (((0+1)+2)+3) //must be performed in left-to-right order, one addition at at
time
- This cannot be parallelized
  * Each operation must be completed before the next one can start

-------------------------
std::reduce() in C++17
-------------------------
- C++17 introduced std::reduce
- This is an alternative implementation of std::accumulate() which is compatible
with prallel execution
  vector<int> vec{1,2,3};
  auto sum = reduce(cbegin(vec), cend(vec), 0); //sum elements of vec
- std::reduce can perform the addition in any order
- compatible with parallel processing
 */

#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

using namespace std;

int main() {
  vector<int> vec(10); // create a vector with 10 elements

  iota(begin(vec), end(vec), 1); // populate vec elements as 1, 2, 3, 4...

  cout << "Vector populated by iota: ";

  for (auto v : vec) {
    cout << v << " ";
  }

  vector<int> vec2(10);
  int n{1};
  for (auto &v : vec2) {
    v = n;
    ++n;
  }

  cout << "\nVector populated by loop: ";
  for (auto v : vec2) {
    cout << v << " ";
  }
  //----------------------------------------------------------------------------
  // accumulate()
  vector<int> vec3{3, 1, 4, 1, 5, 9};
  cout << "\nVector3 is: ";
  for (auto v : vec3) {
    cout << v << " ";
  }
  cout << "\n";
  auto sum = accumulate(cbegin(vec3), cend(vec3), 0); // returns the sum
  cout << "Sum calculated by algorithm: " << sum << "\n";

  sum = 0;
  for (auto v : vec3) {
    sum += v;
  }
  cout << "Sum calculated by loop: " << sum << "\n";
  //----------------------------------------------------------------------------
  // accumulate() with extra argument
  // lambda takes the current running total sum1 and current element of vec3
  // as n
  auto sum1 = accumulate(cbegin(vec3), cend(vec3), 0, [](int sum1, int n) {
    return (n % 2 == 1) ? sum1 + n : sum1;
  });

  cout << "Sum of odd elements: " << sum1 << "\n";
}

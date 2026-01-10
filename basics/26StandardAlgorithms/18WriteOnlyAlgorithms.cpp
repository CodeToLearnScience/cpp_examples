/* Write-only Algorithms
------------------------------
- The standard library defines a few algorithms that write to an iterator range
but do not read any elements
- These are useful for populating sequential containers such as vector and
string

--------
fill()
--------
- fill() assigns a given value to the elements in an iterator range
vector<int> vec(10);                //vector with 10 elements
fill(begin(vec), end(vec), 42);     //Assign 42 to all elements of the vector
- This is equivalent to
  for(auto &v: vec){
    v=42;
  }

-----------
fill_n()
-----------
- fill_n() is similar, but takes a number instead of the second iterator
- This determines how many elements will be assigned
  * starting from the first iterator
- It will return an iterator pointing to the element after the last one which
  was assigned
  //assign 42 to the first 5 elements and 99 to the rest
  auto begin_rest = fill_n(begin(vec), 4, 42); //return an iterator to the 6th
element
  fill(begin_rest, end(vec), 99); //assign the remaining elements to be 99
- fill_n() can be potentially dangerous it assumes that you know what you are
doing. It assumes that this vector has at least 5 elements. It doesn't check
the size of the vector or whether it has reached the last element

------------
generate()
------------
- generate() uses the value retured from calling a function to assign the
elements
- This function takes no arguments
- It returns a value of the element's type
- It should return a different value each time it is called

------------
generate_n()
------------
- generate_n() has the same relation to generate() as fill_n() has to fill()
- It assigns the specified number of elements and returns an iterator to the
first untouched element
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

// functor for demostrating generate() algorithm
class square {
private:
  int n{0};

public:
  int operator()() {
    ++n;
    return n * n;
  }
};

int main() {
  vector<int> vec(10); // crete vector to hold 10 elements

  fill(begin(vec), end(vec), 42);

  for (auto v : vec) {
    cout << v << " ";
  }
  cout << "\n";
  //----------------------------------------------------------------------------
  // fill_n()
  auto begin_rest = fill_n(begin(vec), 5, 43);
  fill(begin_rest, end(vec), 99);

  // if we were to hand-write
  /*
   int i;
   for(i=0; i<5;++i) vec[i]=43;
   for(; i<10;++i) vec[i]=99;
   */

  cout << "Values filled using fill_n algorithms\n";

  for (auto v : vec) {
    cout << v << " ";
  }
  cout << "\n";

  //----------------------------------------------------------------------------
  // to avoid potentially dangerous bugs with fill_n we could do the following
  // as one option
  vector<int> vec1;
  // resize vec to have 5 elements
  if (vec1.size() < 5) {
    // new_vec is local so it will destroyed outside of scope
    vector<int> new_vec(5);
    vec1.swap(new_vec);
  }

  auto begin_rest1 = fill_n(begin(vec1), 5, 42);
  for (auto v : vec1) {
    cout << v << " ";
  }
  cout << "\n";

  // another option is insert operator
  vector<int> vec2;
  auto begin_rest2 = fill_n(back_inserter(vec2), 5, 45);

  /*equivalent
   for(int i=0; i<5; ++i){
     vec2.push_back(45);
   }*/
  for (auto v : vec2) {
    cout << v << " ";
  }
  cout << "\n";

  //----------------------------------------------------------------------------
  // generate()
  vector<int> vec3(10);
  // populate with the first 10 squares
  generate(begin(vec3), end(vec3), square());

  /* equivalent
    square sq;
    for(auto &v: vec3){
     v=sq();
    }
  */
  for (auto v : vec3) {
    cout << v << " ";
  }
  cout << "\n";

  //----------------------------------------------------------------------------
  // generate_n()

  vector<int> vec4;
  generate_n(back_inserter(vec4), 6, square());
  for (auto v : vec4) {
    cout << v << " ";
  }
  cout << "\n";
}

/* -----------------
   Insert Iterators
   -----------------
- An output stream iterator inserts data into an output stream
- An insert iterator adds new elements to a container
- To add a new element, we assign to the insert iterator
- There are three types of iterator, which add an element at different positions
  * std::back_insert_iterator adds an element at the back
  * std::front_insert_iterator adds an element at the front
  * std::insert_iterator adds an element at any given position

------------------
Inserter functions
------------------
- To get an insert iterator, we call an "inserter" function
- We pass the container object as the argument to the inserter
- The function returns an insert iterator for that object
  * back_inserter() returns a back_insert_iterator
  * front_inserter() returns a front_insert_iterator
  * inserter() returns an insert_iterator
---------------------
back_insert_iterator
---------------------
- To add a new element at the back of the container, we assign a value to a
back_insert_iterator
- The push_back() member function of the container will be called. So this works
with containers which supports push_back()
- The value we assign will be passed as the argument to push_back()
- Every time we assign to this iterator, a new element is added at the back of
the container

----------------------
front_insert_iterator
----------------------
- is similar, except it calls push_front()
  * This doesn't work with std::vector or std::string

---------------
insert_iterator
---------------
- inserter() takes a second argument, which is a positional iterator
- This iterator represents the position where new elements will be added

   vector<int> vec={1,2,3};
   auto el2 = next(begin(vec)); // get a positional iterator to the second
element
- The return value is an insert_iterator for the container at that position
  auto it = inserter(vec, el2);
- To add a new element at this postion, we assign to the insert_iterator
  *it = 99; //calls vec.insert(el2, 99);

---------------------------------
Applications of insert iterators
---------------------------------
- Insert iterators can be used anywhere where a positional iterator is expected
- Insert operators are useful for populating containers
  * As arguments to algorithms that copy iterator ranges
  * It conjunction with stream iterators
- The advantage of using an insert iterator is that the container will always
expand to make sure it has enough room. If you use an ordinary iterator, then
you may overflow the container.
 */

#include <algorithm>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

using namespace std;

int main() {

  vector<int> vec;
  cout << "Vector has " << vec.size() << " elements\n";

  cout << "Calling back_inserter()\n";
  auto it = back_inserter(vec); // get an insert iterator for vec

  // assing to this iterator
  cout << "Assigning to insert iterator\n";
  *it = 99; // calls vec.push_back(99)
  *it = 88; // calls vec.push_back(88)

  // vector elements are now {99, 88}
  cout << "Vector has " << vec.size() << " elements\n";

  for (auto v : vec) {
    cout << v << ", ";
  }
  cout << "\n";

  cout << "Calling front_inserter()\n";

  // Source container with elements in ascending order
  std::vector<int> src{1, 2, 3, 4, 5};

  // 1) Insert at front of deque
  std::deque<int> dq;
  std::copy(src.begin(), src.end(), std::front_inserter(dq));
  // dq now contains 5,4,3,2,1 (reverse of src)
  std::cout << "deque: ";
  for (int x : dq) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

  // 2) Insert at front of list
  std::list<int> lst;
  std::copy(src.begin(), src.end(), std::front_inserter(lst));
  // lst now contains 5,4,3,2,1
  std::cout << "list:  ";
  for (int x : lst) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

  // 3) Build container manually using front_insert_iterator
  std::deque<int> dq2;
  auto it1 = std::front_inserter(
      dq2);  // returns std::front_insert_iterator<deque<int>>
  *it1 = 10; // inserts 10 at front
  *it1 = 20; // inserts 20 at front (now 20,10)
  *it1 = 30; // inserts 30 at front (now 30,20,10)
  std::cout << "dq2:   ";
  for (int x : dq2) {
    std::cout << x << ' ';
  }
  std::cout << '\n';

  cout << "Calling inserter()\n";
  vector<int> vec1 = {1, 2, 3};

  // one thing we need to be careful of and this applies to insert operations
  // generally, not just with iterators. So in the following code, after
  // inserter(vec1, el2), status of the iterator el2 is undefined. It is
  // possibly invalid. The reason is that the vector may have done some internal
  // rearrangement. It may have moved the elements around or relocated the
  // buffer. So if you dereference *el2 and and print the results out. The
  // program may crash or output some garbage
  auto el2 = next(begin(vec1));
  auto it2 = inserter(vec1, el2);

  // assign to this iterator
  *it2 = 99;
  for (auto v1 : vec1) {
    cout << v1 << " ";
  }
  std::cout << "\n";

  // stream iterators example
  cout << "Enter some words: " << "\n";
  istream_iterator<string> iis(cin); // iterator to read strings
  istream_iterator<string> eof;      // empty iterator

  vector<string> vec2;
  auto it3 = back_inserter(vec2);
  while (iis != eof) { // do we have any input to read
    it3 = *iis;        // yes-store it in the vector
    ++iis;             // move to the next input
  }
  cout << "You entered " << vec2.size() << " words: ";
  for (const auto &v : vec2) {
    cout << v << " ";
  }
  cout << "\n";
}

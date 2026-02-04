/*
-------------
Set
-------------
- A set is an unstructured collection of elements
- The C++ library provides std::set in <set>
- This is an associative container
- An element consists only of key, which must be unique
  * No duplicates allowed
- The elements of std::set are stored in order
  * By default, the < operator of the key is used to sort the elements
- Foe efficiency, std::set is implemented as a tree
  * Usually a red-black tree

---------------------------
Adding and Reoving Elements
---------------------------
- We use insert() to add an element
  * The set will add the new element in the right place in the tree
- We use erase() to remove an element
These operations may cause the tree to become unbalanced

---------------
Dit it Work?
---------------
- If we try to insert an element into a std::set that is already present, the
insert will fail
  * why?
- insert() returns a std::pair
- The second member is a boolean which is true/false depending on whether the
insert succeeded
- The first member is an iterator to an element in the set
  * The newly added element, if succesful
  * The existing element with that key, if unsuccessful

  -----------------
  Finding Elements
  -----------------
- s.find(k) returns an iterator to the element with key k
  * or end() if k is not found
- s.count(k) returns the number of elements with key k
  * Since duplicates are not allowed, this can only be 0 or 1

----------------------------
std::set and Algorithms
----------------------------
- The elements of std::set are const
- Also, the elements cannot be reordered
  * Why?
- This means that many algorithms cannot be used with std::set
- We can use Algorithms which read a range of std::set iterators
  auto it = find_if(cbegin(s), cend(s), [](int n){return n==7;});

--------------------------
std::set Pros and Cons
--------------------------
- Very fast at accessing an arbitrary element
- Insertion and deletion are usually very fast
  * Can be slow if the internal tree gets unbalanced
- Useful for checking membership (or non-membership)
- USeful when duplicate data is either not needed or not wanted
  * e.g. the number of distinct words in a document
*/

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <set>

using namespace std;

void print(const set<int> &s) {
  cout << "Elements of set: ";
  for (auto el : s) {
    cout << el << ",";
  }
  cout << "\n";
}

int main() {
  set<int> s;  // create an empty std::set
  s.insert(6); // Add some elements to it
  s.insert(7); // The argument to insert() is the key of the element
  s.insert(4);
  s.insert(5);
  s.insert(3);
  print(s);

  auto ret = s.insert(3);
  if (ret.second) {
    cout << "Added element with key 3 to set\n";
  } else {
    cout << "Set already contains element with key " << *(ret.first) << "\n";
  }

  print(s);

  cout << "Removing element with key 3\n";
  s.erase(3);
  print(s);

  auto ret2 = s.insert(3);
  if (ret2.second) {
    cout << "Added element with key 3 to set\n";
  } else {
    cout << "Set already contains element with key " << *(ret.first) << "\n";
  }

  print(s);

  cout << "\nCalling find(7)\n";
  auto it = s.find(7);
  if (it != s.end()) {
    cout << "The set has an element with key " << *it << "\n";
  } else {
    cout << "The set has no element with key 7\n";
  }

  // cout << "Changing element's value to 11\n";
  //*it = 11; //compilation error

  cout << "\nCalling count(7)\n";
  auto n = s.count(7);
  if (n == 1) {
    cout << "The set has 1 element with key 7\n";
  } else {
    cout << "The set has 0 elements with key 7\n";
  }

  {
    cout << "\nCalling find(7) with find_if algorithm and predicate\n";
    auto it = find_if(cbegin(s), cend(s), [](int n) { return n == 7; });
    if (it != s.end()) {
      cout << "The set has an element with key " << *it << "\n";
    } else {
      cout << "The set has no element with key 7\n";
    }
  }
  {
    cout << "\nCalling count(7) woth count_if and predicate\n";
    auto n = count_if(cbegin(s), cend(s), [](int n) { return n == 7; });
    if (n == 1) {
      cout << "The set has 1 element with key 7\n";
    } else {
      cout << "The set has 0 elements with key 7\n";
    }
  }
}

/*
 ----------------
 List operations
 ----------------
 - Lists support many of the operations we would expect for a sequential
 container
   * we can use push_back() and push_front() to add elements
   * We can use iterators to loop over the elementsof a list
- However, lists do not support random access
  * We cannot jump straight to, for example, the sixth element
    - SO this means that the functions in the header, which require random
      access are not supported like generic sort()
  * We have to start at the beginning of the list and iterate the required
number of times

----------
sort()
----------
- The generic sort() algorithm requires random access to container elements
- This is not supported for list and forward_list
   sort(begin(l), end(l)); //does not compile
- Instead, we have to use the member function
   l.sort();

------------------------
List Member Operations
------------------------
- In some cases, the list member function versions of algorithms are faster than
the generic equivalents
- The generic version of remove() shuffles the removed elements to the end of
the container
- The list member function version deletes the elements immediately
  * This just changes a couple of pointers
  * No need to call erase()

----------------------------------
Operations which move elements
----------------------------------
- In general, if you are going to be moving elements around, its much better to
use the list member function
- reverse
  * REverses the order
- remove
  * Deletes certain elements from the list
- remove_if
  * Deletes elements from the list which match certain criteria
- unique
  * Deletes duplicate elements from the list
- These all modify the object they are called  on

----------
merge()
----------
- There are also some functions which are specific to list
- merge() will remove elements from the argument list and merge them into the
"this" list
- The list will be sorted in ascending order, provided both lists were sorted
before the operation
 list<int> l2{1,7,12,24};
 list<int> l3{9,3,14};

 l2.sort(); //sort the lists before merging
 l3.sort();
 l2.merge(l3); //l2 now contains 1,3,7,9,12,14,24

 ---------
 splice()
 ---------
 - splice() moves elements from another list into a list
 - The first argument is an iterator to an element in "this" list
   * The elements will be inserted just before that element
- THe second argument is the list to be spliced in
   list<int> l4{1,12,6,24};
   list<int> l5{9,3,14};

   auto p = begin(l4);
   advance(p,1);    // p is an iterator to the second element
   l4.splice(p,l5); // l4 now contains {1,9,3,14,12,6,24} and l5 is empty
- There are also versions which move a single element or a range of elements
from the argument list

------------------------------
splice() and std::forward_list
------------------------------
- std::forward_list implements splice_after() Instead of splice
- This workds almost the same way as splice() does for std::list
- However, the elements are spliced in after the iterator argument,
    instead of before it
    forward_list<int> l6{1,12,6,24};
    forward_list<int> l7{9,3,14};
    auto p = begin(l6);
    l6.splice_after(p,l7); //l4 now contains {1,9,3,14,12,6,24}

 */

#include <forward_list>
#include <iostream>
#include <list>

using namespace std;

int main() {
  list<int> l{4, 3, 1};

  cout << "Initial elements in list \n";
  for (auto el : l) {
    cout << el << ", ";
  }

  cout << "\n";

  // sort(begin(l), end(l)); //will not compile
  l.sort();

  cout << "Elements in list after sorting \n";

  for (auto el : l) {
    cout << el << ", ";
  }

  cout << "\n";

  l.remove(3);

  cout << "Elements in list after removing 3 \n";

  for (auto el : l) {
    cout << el << ", ";
  }

  cout << "\n";

  list<int> l1{1, 7, 12, 24};
  list<int> l2{9, 3, 14};

  cout << "Elements in list 1 \n";
  for (auto el : l1) {
    cout << el << ", ";
  }

  cout << "\n";

  cout << "Elements in list 2 \n";
  for (auto el : l2) {
    cout << el << ", ";
  }

  cout << "\n";

  l1.sort(); // sort the lists before merging
  l2.sort();
  l1.merge(l2); // l2 now contains 1,3,7,9,12,14,24

  cout << "Elements in list1 after merge \n";
  for (auto el : l1) {
    cout << el << ", ";
  }
  cout << "\n";

  cout << "Elements in list2 after merge \n";
  for (auto el : l2) {
    cout << el << ", ";
  }
  cout << "\n";

  // splice()----------------------------------------------------------------
  list<int> l4{1, 12, 6, 24};
  list<int> l5{9, 3, 14};
  cout << "Elements in list4 \n";
  for (auto el : l4) {
    cout << el << ", ";
  }

  cout << "\n";

  cout << "Elements in list5 \n";
  for (auto el : l5) {
    cout << el << ", ";
  }
  cout << "\n";

  auto p = begin(l4);
  advance(p, 1);    // p is an iterator to the second element
  l4.splice(p, l5); // l4 now contains {1,9,3,14,12,6,24} and l5 is empty

  cout << "Elements in list4 after splice \n";
  for (auto el : l4) {
    cout << el << ", ";
  }
  cout << "\n";

  cout << "Elements in list5 after splice \n";
  for (auto el : l5) {
    cout << el << ", ";
  }
  cout << "\n";

  // splice_after()----------------------
  cout << "\n----splice_after()------\n";

  forward_list<int> l6{1, 12, 6, 24};
  forward_list<int> l7{9, 3, 14};
  cout << "Elements in list6 \n";
  for (auto el : l6) {
    cout << el << ", ";
  }

  cout << "\n";

  cout << "Elements in list7 \n";
  for (auto el : l7) {
    cout << el << ", ";
  }
  cout << "\n";

  auto p1 = begin(l6);
  l6.splice_after(p1, l7);

  cout << "Elements in list6 after splice \n";
  for (auto el : l6) {
    cout << el << ", ";
  }
  cout << "\n";

  cout << "Elements in list7 after splice \n";
  for (auto el : l7) {
    cout << el << ", ";
  }
  cout << "\n";
}

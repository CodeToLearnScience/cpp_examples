/*---------------------
 Sorting Algorithms
---------------------
- Sorting algorithms put the elements in an iterator range into order
- By default, the elements < operator is used
- We can override this by providing our own comparison function

--------------
sort()
--------------
- sort() orders elements in ascending order
- Usually implemented as a "quicksort" as its the fastest in general case
- Elements which have the same key may have their order changed

----------------------
sort() with predicate
----------------------
- We can supply a comparison function as an optional argument
- This will be used instead of the < operator to order the elements

--------------------
is_sorted()
--------------------
- is_sorted() returns a bool, depending on whether the iterator range is sorted

-----------------
is_sorted_until()
-----------------
- is_sorted_until() returns an iterator to the first element which is not in
oder

-------------------
partial_sort()
-------------------
- Sometimes we only need to sort part part of the container
  * e.g.display the first 20 results only
- In this case, we can use a partial_sort
   * The first 20 elements wil be in order
   * The elements which come after these will not be ordered
- This is faster than doing a complete sort
- partial_sort() takes an extra iterator
- The offset of this iterator gives the number of elements we want in the result
- e.g. begin() + 5 gives the first 5 results
  string keys{"afshgfuqlasfhsfasgur"};
  partial_sort(begin(keys), begin(keys), end(keys));

---------------------
partial_sort_copy()
---------------------
- partial_sort_copy() does a partial sort and stores the result in a destination
- This will sort as many elements as will fit into "dest" and write them there
  * If the destination is large enough, it will sort the entire range

--------------------
nth_element()
--------------------
- nth_element() takes an iterator to an element in the range
- It rearranges the elements so that the iterator points to the element that
would be in that position if the range was sorted
  * e.g. if the iterator is begin() + 3
  * The iterator will point to the element which ranks 4th
- It them performs a partition with this element as the partition point
  * All the elements before it will have a lower value or equal
  * All the elements after it will not have a lower value
*/

#include <algorithm>
#include <ios>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

class student {
  std::string name; // student name not necessarily unique
  int id;           // student id number - unique to each student

public:
  student(std::string name, int id) : name(name), id(id) {}
  friend bool operator==(const student &lhs, const student &rhs);
  friend bool operator!=(const student &lhs, const student &rhs);
  friend bool operator<(const student &lhs, const student &rhs);
  void print();
};

bool operator==(const student &lhs, const student &rhs) {
  if (lhs.id == rhs.id) {
    return true;
  }
  return false;
}

bool operator!=(const student &lhs, const student &rhs) {
  return !(lhs == rhs);
}

bool operator<(const student &lhs, const student &rhs) {
  return (lhs.name < rhs.name); // order by name (alphabetical sort)
}

void student::print() { cout << "Name: " << name << ", id: " << id << "\n"; }

int main() {
  student stu1("John Smith", 561234);
  student stu2("John Smith", 453811);
  student stu3("Jack Jones", 692837);
  student stu4("Jack Jones", 692837);

  vector<student> students = {stu1, stu2, stu3, stu4};
  cout << "Vector before sorting: \n";
  for (auto student : students) {
    student.print();
  }

  // the "John Smith" students may be in either order
  sort(begin(students), end(students));

  cout << "Vector after sorting: \n";
  for (auto student : students) {
    student.print();
  }

  cout << "If you want to retain the order, you can use stable_sort():\n";
  stable_sort(begin(students), end(students));
  cout << "Vector after stable_sort(): \n";
  for (auto student : students) {
    student.print();
  }
  //---------------------------------------------------------------------------
  // sort with predicate
  vector<int> vec{3, 1, 4, 1, 5, 9};
  cout << "Vec before sort: ";
  for (auto v : vec) {
    cout << v << " ";
  }
  cout << "\n";
  cout << "vec is sorted: " << boolalpha << is_sorted(begin(vec), end(vec))
       << "\n";
  sort(begin(vec), end(vec), [](int m, int n) { return m > n; });
  cout << "Vec after sort with use of predicate to sort in descending order: ";
  for (auto v : vec) {
    cout << v << " ";
  }
  cout << "\n";
  cout << "vec is sorted: " << boolalpha
       << is_sorted(begin(vec), end(vec), [](int m, int n) { return m > n; })
       << "\n";
  //---------------------------------------------------------------------------
  // is_sorted_until
  vector<int> vec1{1, 4, 5, 6, 2, 7, 5};
  cout << "vec: ";
  for (auto v : vec1) {
    cout << v << " ";
  }
  cout << "\n";
  auto el = is_sorted_until(cbegin(vec1), cend(vec1));

  if (el != cend(vec1)) {
    cout << "The first " << distance(cbegin(vec1), el)
         << " elements are sorted\n";
    cout << "The first element which is not in order has value " << *el << "\n";
  } else {
    cout << "Could not find an intial sequence which is sorted\n";
  }
  //---------------------------------------------------------------------------
  // partial_sort
  cout << "++++++++++++demonstration of partial_sort()++++++++++++++\n";
  string keys{"qwertyuiopasdfghjkl"};
  cout << "keys: " << keys << "\n";
  auto it = begin(keys);
  partial_sort(it, it + 5, end(keys));
  cout << "First 5 characters of keys are: " << keys.substr(0, 5) << "\n";
  cout << "Full keys string: " << keys << "\n";
  advance(it, 5);
  partial_sort(it, it + 5, end(keys));
  cout << "The next 5 characters of keys are: " << keys.substr(5, 10) << "\n";
  cout << "Full keys string: " << keys << "\n";
  //---------------------------------------------------------------------------
  // partial_sort_copy
  cout << "++++++++++++demonstration of partial_sort_copy()++++++++++++++\n";
  string keys1{"qwertyuiopasdfghjkl"};
  string dest(5, ' ');
  cout << "keys1: " << keys1 << "\n";
  partial_sort_copy(cbegin(keys1), cend(keys1), begin(dest), end(dest));
  cout << "First 5 characters of keys1 are: " << dest << "\n";
  cout << "Full keys string: " << keys1 << "\n";
  //---------------------------------------------------------------------------
  // nth_element()
  cout << "++++++++++++demonstration nth_element()++++++++++++++\n";
  vector<int> vec2{1, 4, 5, 6, 2, 7, 5};
  vector<int> vec3{vec2};
  cout << "vec: ";
  for (auto v : vec2) {
    cout << v << " ";
  }
  cout << "\n";

  sort(begin(vec3), end(vec3));

  cout << "vec if sorted: ";
  for (auto v : vec3) {
    cout << v << " ";
  }
  cout << "\n";

  cout << "Calling nth_element" << "\n";
  auto mid = begin(vec2) + 4;
  nth_element(begin(vec2), mid, end(vec2));
  cout << "The mid element is " << *mid << "\n";
  cout << "vec: ";
  for (auto v : vec2) {
    cout << v << " ";
  }
  cout << "\n";
}

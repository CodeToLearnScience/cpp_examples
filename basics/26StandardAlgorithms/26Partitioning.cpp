/*
----------------
Partitioning
----------------
- We can "partition" the elements in a container into two groups
  * Elements which have some property are at the front of the container
  * Elements which do not have that property are at the back of the container
- The partition point marks the boundary between the two groups
- Partitioning is very useful, especially in interactive applications
  * Display unread messages before messages which have been read
  * Display list items selected by the user above unselected items
-----------
partition()
-----------
- partition() takes an iterator range and a predicate function
- All elements for which the predicate function returns true are moved to the
front of the range
- All elements for which predicate function returns false are moved to the back
of the range
- The elemetns within each group may not be in order
  //partition by oddness: move all odd elemetns to the front
  partition(begin(vec), end(vec), [](int n){return n%2==1);});

------------------
stable_partition()
------------------
- stable_partition() is the same partition(), except the elements within a group
will keep thier relative order
- longer execution time
  vector<int> vec{3,1,4,1,5,9};
  stable_partition(begin(vec), end(vec), [](int n){return n%2==1;});

  //results will be: {3,1,1,5,9,4}

-----------------------
is_partitioned()
-----------------------
- is_partitioned() takes an iterator range and a predicate function
- It returns a bool depending on whether the range of elements is already
is_partitioned by that predicate

-------------------
partition_point
-------------------
- partition_point() takes the same argument as is_partitioned()
- It returns an iterator to the first element for which the predicate is false
- If we have a container which is already partitioned, we can use this to find
the partition point
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
  vector<int> vec{3, 1, 4, 1, 5, 9, 2, 8, 6};
  cout << "vec: ";
  print(vec);

  // partition by oddness: move all odd elements to the front
  // relative order can change
  partition(begin(vec), end(vec), [](int n) { return n % 2 == 1; });

  cout << "vec after partition(): ";
  print(vec);
  //--------------------------------------------------------------------------
  // stable_partition()
  cout << "================demonstration of stable_partition()=============\n";
  vector<int> vec1{3, 1, 4, 1, 5, 9, 2, 8, 6};
  stable_partition(begin(vec1), end(vec1), [](int n) { return n % 2 == 1; });
  cout << "vec after stable_partition(): ";
  print(vec1);

  //--------------------------------------------------------------------------
  // if_partititioned()
  cout << "================demonstration of is_partitioned()=============\n";
  auto is_odd = [](int n) { return n % 2 == 1; };
  // are all the odd elements at the front of the vector?
  if (is_partitioned(cbegin(vec), cend(vec), is_odd)) {
    cout << "vec is partitioned by the oddness\n";
  } else {
    cout << "vec is not partitioned by the oddness\n";
  }

  //--------------------------------------------------------------------------
  // partitition_point()
  cout << "================demonstration of partitition_point()=============\n";
  auto partition_pt = partition_point(cbegin(vec), cend(vec), is_odd);

  if (partition_pt != cend(vec)) {
    cout << "The partition point is an element with value " << *partition_pt;
    cout << " which is at index " << distance(cbegin(vec), partition_pt)
         << "\n";
  } else {
    "vec is not partitioned by is_odd\n";
  }
}

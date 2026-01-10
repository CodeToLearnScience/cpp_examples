/*
 -------------------
 Removing algorithms
 -------------------
 - Removing algorithms are used to remove elements from a range
 - However, the elements are "logically" removed
 - They are still physically present in the range
----------------------
remove()
----------------------
-Each element which has a given value is moved back of the range
 * The removed elements still exit in the container
 * the value of the removed elements are no nolonger defined
 * accessing them will cause undefined error
- The elements which were behind it are moved forwards
  * Calling size will return the same value as before
- remove() returns an iterator to the first removed element

---------------
erase()
---------------
- To physically remove these elements, we call the containers erase() member
function
- we pass returned iterator as the first argument

------------------------
remove_if() and _copy()
------------------------
- remove_if() takes a predicate
- _copy() versions write to a destination
- remove() uses the equality == operator

--------------
remove_copy()
--------------
- remove_copy() writes the result to a destination
- it performs a copy operation, which omits the matching elements
- This is equivalent to copying all the elements which are not equal to the
value

-------------------
remove_copy_if()
-------------------
- remove_copy_if() is similar, but takes a lambda (predicate)
- This can also be written using copy if()

--------------
unique()
--------------
- unique() removes duplicate adjacent elements
- The elments in the iterator range must be sorted
- unique() behaves similarly to remove() in that the elements are only
"logivally" removed
- To physically remove them, pass the returned iterator to erase()
- unique() uses the == operator
- we can also provide our own predicate
  auto defunt = unique(begin(vec), end(vec), [](int m, int n){
    return (n==m+1);
  })
- The predicate will take 2 arguments, which correspond to successive elements
- In this case we want to remove elements which differ by one. So if we have
3 followed 4, then we want to remove the elements with value 4

------------------
unique_copy()
------------------
- unique_copy() writes the result to a destination
- It performs a copy operation, which omits duplicates of elements
- It can also take a predicate
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {

  vector<int> vec{3, 1, 4, 1, 5, 9};
  cout << "original vector: ";

  for (auto v : vec) {
    cout << v << " ";
  }

  cout << "\nBefore calling remove, the vector has " << vec.size()
       << "elements";

  auto defunct = remove(begin(vec), end(vec), 1);

  cout << "After calling remove, the vector has " << vec.size()
       << " elements\n";
  cout << " Result of removal: ";

  for (auto v : vec) {
    cout << v << " ";
  }
  cout << "\n";

  cout << "Erase algorithm\n";
  vec.erase(defunct, end(vec));
  cout << "After calling the erase, the vector has " << vec.size()
       << " elements\n";

  for (auto v : vec) {
    cout << v << " ";
  }

  //---------------------------------------------------------------------------
  // remove_if()
  // lets take the same vector again
  vector<int> vec1{3, 1, 4, 1, 5, 9};
  auto defunct1 =
      remove_if(begin(vec1), end(vec1), [](int n) { return (n % 3 == 0); });

  vec1.erase(defunct1, end(vec1));
  cout << "After calling the erase, on the vec after removing from remove_if. "
          "Here we are removing elements which are divisible by 3 "
       << vec1.size() << " elements\n";

  for (auto v : vec1) {
    cout << v << " ";
  }
  cout << "\n";
  //---------------------------------------------------------------------------
  // remove_copy()
  cout << "Demonstrating remove_copy(): \n";
  vector<int> vec2{3, 1, 4, 1, 5, 9};
  cout << "Original vector: ";
  for (auto v : vec2) {
    cout << v << " ";
  }
  vector<int> vec3;

  remove_copy(cbegin(vec2), cend(vec2), back_inserter(vec3), 1);

  cout << "Result of remove copy: ";
  for (auto v : vec3) {
    cout << v << " ";
  }
  cout << "\n";
  //---------------------------------------------------------------------------
  // remove_copy_if()

  cout << "Demonstrating remove_copy_if(): \n";
  vector<int> vec4{3, 1, 4, 1, 5, 9};
  cout << "Original vector: ";
  for (auto v : vec4) {
    cout << v << " ";
  }
  cout << "\n";
  vector<int> vec5;

  remove_copy_if(cbegin(vec4), cend(vec4), back_inserter(vec5),
                 [](int n) { return (n % 3 == 0); });

  cout << "Result of remove copy, remove the elements which are divisible by 3 "
          "and copy rest: ";
  for (auto v : vec5) {
    cout << v << " ";
  }
  cout << "\n";

  cout << "Above one can be implemented using copy_if() and by inverting "
          "predicate\n";
  vector<int> vec6;
  copy_if(cbegin(vec4), cend(vec4), back_inserter(vec6),
          [](int n) { return (n % 3 != 0); });
  for (auto v : vec6) {
    cout << v << " ";
  }
  cout << "\n";
  //---------------------------------------------------------------------------
  // unique()
  cout << "Demonstrating unique(): \n";
  vector<int> vec7{3, 1, 4, 1, 5, 9};
  cout << "Original vector: ";
  for (auto v : vec7) {
    cout << v << " ";
  }
  cout << "\n";
  // sort the vector so that duplicate elements are adjacent to each other
  sort(begin(vec7), end(vec7));
  cout << "Sorted vector: ";
  for (auto v : vec7) {
    cout << v << " ";
  }
  cout << "\n";
  cout << "\nBefore calling remove, the vector has " << vec7.size()
       << "elements \n";

  auto defunct2 = unique(begin(vec7), end(vec7));
  cout << "\nBefore calling erase, the vector has " << vec7.size()
       << " elements: ";
  for (auto v : vec7) {
    cout << v << " ";
  }
  cout << "\n";

  vec7.erase(defunct2, end(vec7));
  cout << "\nAfter calling erase, the vector has " << vec7.size()
       << " elements: ";
  for (auto v : vec7) {
    cout << v << " ";
  }
  cout << "\n";
  //---------------------------------------------------------------------------
  // unique() with predicate
  cout << "Demonstrating unique() with predicate; \n";
  vector<int> vec8{3, 1, 4, 1, 5, 9};

  sort(begin(vec8), end(vec8));
  cout << "Sorted vector: ";
  for (auto v : vec7) {
    cout << v << " ";
  }
  // this will move 4 to back which is 1 more than 3 its predecessor value.
  // Since no other value sequence has one more than previous so only it will be
  // removed
  auto defunt3 =
      unique(begin(vec8), end(vec8), [](int m, int n) { return (n == m + 1); });
  // erase will delete that 4
  vec8.erase(defunt3, end(vec8));
  cout << "Result of unique() with predicate and erase: ";
  for (auto v : vec8) {
    cout << v << " ";
  }

  cout << "\n";
  //---------------------------------------------------------------------------
  // unique_copy() with predicate
  cout << "Demonstrating unique_copy(): \n";
  vector<int> vec9{3, 1, 4, 1, 5, 9};

  sort(begin(vec9), end(vec9));
  cout << "Sorted vector: ";
  for (auto v : vec9) {
    cout << v << " ";
  }
  cout << "\n";

  vector<int> vec10;
  unique_copy(cbegin(vec9), cend(vec9), back_inserter(vec10));
  cout << "Result of calling unique_copy: ";
  for (auto v : vec10) {
    cout << v << " ";
  }
  cout << "\n";
}

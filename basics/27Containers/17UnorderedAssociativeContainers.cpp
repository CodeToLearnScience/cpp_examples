/*
----------------------------------------
Unordered Associative Containers
----------------------------------------
- Associative containers store their elements in an order which depends on the
key
- std::set, std::map etc use a tree
- C++11 introduced "unsorted" associative containers
  * These use a "hash table"
- In C++ terms, the hash-table is an array of "buckets"

----------------------------------
Unordered Container Implementation
----------------------------------
- In an Unordered container, the buckets are linked lists of pointers to the
container's elements
- The index of the array is calculated from the element
  * A "hash function" generates a number based on the key
  * This is known as the "hash" of the key
  * This is usually a very fast operation
  * The hash of the key is used as the index into the array

-----------------
Element insertion
-----------------
- Calculate the hash number of the new element's key
- Find the bucket which corresponds to that number
- Push a pointer to the new container element onto that buckets list

----------------
Element search
----------------
- Calculate the hash number of the key
- Use that number to indentify the bucket to search
- Search the bucket for the element(s) with the required key
* uses the == operator of the key's type

----------------
Hash Collisions
----------------
- For maximum efficiency, each element should have its own bucket
  * Each key produces a different hash value
  * This requires the hash function to perform "Perfect hashing"
- In practice, the different keys sometimes give the same hash number
  * A "hash collision"
- In a multimap or multiset, several elements can have the same key
- The more elements there are in a bucket, the longer it will take to perform an
operation which involves that bucket

--------------------------
C++ Unordered Containers
--------------------------
- C++11 provides unordered versions of all the associative containers
  * unordered_set
  * unordered_multiset
  * unordered_map
  * unordered_multimap

----------------------------
Operations
----------------------------
- Unsorted containers support typical associative container operations such as
insert(), find() and erase()
  * These are also operations for managing the buckets
- Operations on un unosorted container are usually faster than they are on a
sorted container
  * Especially for large containers, with many insert() and erase() operations
- However, they can be considerably slower if the hash table needs to be resized
, or if there are many collisions
  * In time-critical applications, this delay may not be acceptable

---------------
Iterators
---------------
- Unordered containers only allow forward iteration
  * rbegin() and rend() and crbegin() and crend() are not supported
  * An iterator to an unordered container connot be decremented
- As the containers have no concept of order, iterator ranges are not
particularly useful
- Except for
  * Iterating over the entire container (forwards only!)
  * Iterating over elements with the same key (multiset/multimap)

-------------------------------
Unordered Multiset and Multimap
-------------------------------
- The unordered versions of multiset and multimap do not support lower_bound()
    and upper_bound()
    * We can still use equal_range()
    * We can also use find() and count()

------------------------------------------------------
Sorting an Unsorted container
------------------------------------------------------
- Sometimes we need to have the elements sorted, but using a sorted container
would add too much overhead
- In this case, we can use an unsorted contaner and copy its elements into a
sorted container
  unordered_map<key, value> u_map;
  ...
  ...
  map<key, value> s_map;

  //copy into the ordered map
  //As we populate s_map with elements, it will automatically sort them
  copy(begin(u_map), end(u_map), inserter(s_map, end(s_map)));

*/

// example of simple hash-map
#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <random>
#include <unordered_map>

using namespace std;

void simple_hash_table_example() {
  mt19937 mt;
  uniform_int_distribution<int> dist(1, 100);

  // the hash table is an array of linked lists
  std::array<list<int>, 10> buckets;
  // generate 150 random numbers with values between 1 and 100
  // if between 1 and 100, put into buckets[0]
  // if between 11 and 20, put into buckets[1], etc
  for (int i = 0; i < 150; ++i) {
    int num = dist(mt);       // get a random numbers
    int idx = (num - 1) / 10; // "hash function" to compute the hash value
    buckets[idx].push_back(
        num); // use the hash value as the index into the array
  }

  // print out the contents of the buckets
  for (int i = 0; i < 10; ++i) {
    auto bucket = buckets[i];
    cout << "Bucket " << i << ": ";
    for (auto n : bucket) {
      cout << n << ", ";
    }
    cout << "\n";
  }
  cout << "\n";

  // find "43" in the hash map
  int target{43};
  int idx = (target - 1) / 10; // compute the hash value

  cout << "Looking for " << target << " in bucket " << idx << "\n";
  auto it = find(cbegin(buckets[idx]), cend(buckets[idx]), target);

  if (it != cend(buckets[idx])) {
    cout << "Found " << target << " in bucket " << idx << "\n";
  }
}

void unordered_map_ex() {
  unordered_map<string, int> scores;
  scores.insert({"Graham", 78});
  scores.insert({"Grace", 66});
  scores.insert({"Graham", 66}); // duplicates will be ignored
  scores.insert({"Graham", 66});
  scores.insert({"Hareesh", 77});

  for (auto it : scores) {
    cout << it.first << " has a score of " << it.second << "\n";
  }
}
//=============================================================================
void unordered_multimap_ex() {
  unordered_multimap<string, int> scores;
  scores.insert({"Graham", 78});
  scores.insert({"Grace", 66});
  scores.insert({"Graham", 66}); // duplicates will be ignored
  scores.insert({"Graham", 66});
  scores.insert({"Hareesh", 77});

  cout << "Unsorted:\n";
  for (auto it : scores) {
    cout << it.first << " has a score of " << it.second << "\n";
  }

  multimap<string, int> sorted_scores;
  // copy into otdered map
  // As we populate sorted_scores with the elements, it will automatically sort
  // them
  copy(begin(scores), end(scores), inserter(sorted_scores, end(sorted_scores)));
  cout << "\nSorted:\n";
  for (auto it : sorted_scores) {
    cout << it.first << " has a score of " << it.second << "\n";
  }
}

int main() {
  simple_hash_table_example();

  cout << "++++++++++++Demonstration of unordered_map++++++++++++++++++\n";
  unordered_map_ex();
  cout << "++++++++++++Demonstration of "
          "unordered_multimap++++++++++++++++++\n";
  unordered_multimap_ex();
}

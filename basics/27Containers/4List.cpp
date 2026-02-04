/*
 ------------------
 Doubly-linked list
 ------------------
 - In a Doubly-linked list, each node has a link to the previous node as well as
 to the next node
 - A Doubly-linked list can easily traversed backwards as well as forwards, by
 following the pointer to the previous node
 - The C++ STL provides std::list to implement Doubly-linked list

 ---------------------
 Appending an element
 ---------------------
 - To add an element at the back of the list
   * Create a node for it
   * Make the last node's "next" link point to it
   * Make our "previous" link point to the last node
   * The added node is now the last node
- The other elements are left untouched

---------------------------------
Inserting an element
---------------------------------
- To insert a node in the middle of a linked list
  * Make the new node's "next" link point to the following node
  * Make the new node's "previous" link point to the before node
  * Make the before node's "next" link point to the new node
  * Make the following node's "previous" link point to the new node
- The other elmenets are left untouched

-------------------
Removing an element
-------------------
- To remove an element from a linked list
  * Make the "net" link of the before node point to the following node
  * Make the following node's "previous" link point to the before node
  * Destroy the node
- Again, the other elements are left untouched

-------------------------
List Pros and Cons
-------------------------
- Adding or removing elements from the middle of a list is faster than for
vector
- Lists do not support indexing or subscript notation
- Accessing an element is slower than for vector
- Lists use more memory to store an element than vector
- Lists are useful where we expect to add or remove a lot of elements frequently
 */

#include <iostream>
#include <iterator>
#include <list>

using namespace std;

int main() {
  list<int> l{1, 4, 3};

  cout << "Initial elements in list \n";
  for (auto el : l) {
    cout << el << ", ";
  }
  cout << "\n";

  auto last = end(l);
  advance(last, -1);            // i is an iterator to the last element
  auto two = l.insert(last, 2); //  Insert a new element before the last element

  cout << "Elements in list after inserting 2 \n";
  for (auto el : l) {
    cout << el << ", ";
  }
  cout << "\n";

  l.erase(two);

  cout << "Elements in list after erasing 2 \n";
  for (auto el : l) {
    cout << el << ", ";
  }
  cout << "\n";
}

/*-----------------------
 Forward List
 ------------------------
- The containers we have looked at so far like vector and string and array use
a single block of memory
- In a list, each element has its own memory allocation ("node")
- Each node contains th element value and a pointer
- The pointer stores the address of the next node in the list
  * The last node will have an invalid link pointer
  * This signifies that it does not have a next node

------------------
Last iteration
------------------
- To iterate through a list, we start with the first node
- We get its link pointer
- We then go to that address, which is the second node
- We then use that node's link pointer to go to the third node and so on...
- When we get to a node which has an invalid link pointer, we stop

----------------
Forward List
----------------
- This data structure is known as a Forward List or singly-linked list
  * Each node has a single link
  * We can iterate forwards through the list by following the links
  * Going backwards through the list is more difficult
- The C++ STL provides std::forward_list which implements this data structure

-----------------
Adding an Element
-----------------
- To add an element at the back of a linked list
  * Create a node for it
  * Make the last node's link point to it
  * The added node is now the last node
- To insert a node in the middle of a linked list
  * Make the link from the node before point to the new node
  * THen make the new node's link point to the node after
- The other elements are left untouched

--------------------
Removing an Element
--------------------
- To remove an element from a linked list
  * Make the previous node link point to the next node
  * Destroy the node
- Again, the other elements are left untouched

---------------------------------
std::forward_list operations
---------------------------------
- List operations are a bit different from the other sequential containers
- Usually, sequential containers have insert() and erase() member functions
  * These add or remove an element before a given location
  * This requires that the containers supports reverse iterators
- std::forward_list only supports forward iterators
  * To add or remove an element, use insert_after() and erase_after()
  * These will add or remove an element after a given location
 */

#include <forward_list>
#include <iostream>
#include <iterator>

using namespace std;

int main() {
  forward_list<int> l{4, 3, 1}; // create a list object

  cout << "Initial element in list" << "\n";
  for (auto el : l) {
    cout << el << ", ";
  }
  cout << "\n";

  auto second = l.begin();
  advance(second, 1);        // i is an iterator to the second element
  l.insert_after(second, 2); // isert a new element after the second element

  cout << "Elements in list after inserting 2" << "\n";

  for (auto el : l) {
    cout << el << ", ";
  }
  cout << "\n";

  l.erase_after(second); // remove this element
  cout << "Elements in list after erasing 2" << "\n";

  for (auto el : l) {
    cout << el << ", ";
  }
  cout << "\n";
}

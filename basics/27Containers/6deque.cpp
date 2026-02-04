/*
---------
Deque
---------
- std::deque implements a double-ended queue
  * similar to vector, but elements can also be added efficiently at the front
  * defined in <deque>
- implemented as a two-dimensional array
  * std::vector has one memory block which stores all the elements
  * std::list has one memory block per element
  * std::deque has multiple memory blocks which each store several elements
- std::deque stores its elements over severa blocks of memory
  * Iterating from the first element of the firstblock to the last element of
    the last block will return all the elements in order
- std::deque has a similar interface to std::vector
- deque also has a push_front() member function
  * This inserts an element before the first element
- If there is not enough room to store a new element, the deque will allocate
another memory block and store it in there
  * The existing elements remain where they are
  * This is different from std::vector, this will allocate a new block, copy all
  the data and release the old block

----------------------------------
Chosing a Sequential Container
----------------------------------
- Deque is slighyly slower than for vector for most operations
  * However, is is faster than vector for adding and removing elements at the
  front of the container
- List is much slower than vector and deque for most operations, and uses more
memory
  * However, list is much faster at adding and removing elements
  * But only of this does not involve searching
- Vector should be the default choice
  * Modern hardware is optimized for accessing contiguous blocks of memory
*/

#include <deque>
#include <iostream>

using namespace std;

int main() {
  deque<int> dq{4, 2, 3, 5, 1};
  dq.push_back(4);
  dq.push_back(2);
  dq.push_front(1);
  dq.push_front(5);
  dq.push_front(3);

  for (auto it : dq) {
    cout << it << ", ";
  }
  cout << "\n";
}

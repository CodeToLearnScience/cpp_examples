/*
-----------
std::queue
-----------
- A queue is a data structure in which elements are stored in the order in which
they are inserted
- As a queue is processed, the element at the front is removed and the element
behind it moves to the front
- When new elements are added to the queue, the are inserted at the back
- Elements can only be removed from the front, in the same order they were added

--------------------
Queue Implementation
--------------------
- C++ has an std::queue Implementation in <queue>
- The first element to be added to the queue is always the first element to be
removed
- The queue is "First in, First out" data structure (FIFO)
- A queue is usually implemented as a deque (why?), although it can be
implemented as a vector or list
  * Reason is there are lot of operations at the front of the container

------------------
Queue operations
------------------
- Queues have a limited interface
  * Use push() to add an element to the back of the queue
  * Use pop() to remove the element from the front of the queue
  * front() returns the elements at the front of the queue
  * back() returns the element at the back of the queue
  * empty() returns true if there are no elements in the queue
  * size() returns the number of elements in the queue
- No support for other typical container operations

------------------------
Queue Applications
------------------------
- Queues are mainly used for temporarily storing data in the order it arrived
  * Network data packets waiting for CPU time
  * Must be processed in sequence
- Inventory system for perishable goods
  * Oldest goods must be shipped first

---------------------
Queue Pros and Cons
---------------------
- Useful for processing events in the order they occur
- Can only access the front element
  * If you need to access other elements, use a vector or a map (with the
    arrival order as the key) instead of a queue
- No provison for "queue jumping" which is often needed in real world
applications
  * A patient arriving at hospital needs emergency treatment
  * An aeroplane is delayed and misses its take-off slot
*/

#include <cstdio>
#include <iostream>
#include <queue>

using namespace std;

void print(const queue<int> &q) {
  cout << "The queue is " << (q.empty() ? "" : "not") << " empty\n";
  cout << "The queue contains " << q.size() << " elements\n";
  cout << "The first element is " << q.front() << "\n";
  cout << "The last element is " << q.back() << "\n";
}

int main() {
  queue<int> q;
  q.push(4);
  q.push(3);
  q.push(5);
  q.push(1);

  print(q);

  // insert a new element at the end of the queue
  cout << "\nAdding element with value 2\n";
  q.push(2);
  print(q);

  // remove the first element
  cout << "\nRemoving first element\n";
  q.pop();
  print(q);
}

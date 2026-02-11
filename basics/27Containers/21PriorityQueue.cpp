/*
--------------------------
Priority Queue
--------------------------
 - With a standard queue, the elements are arranged strictly in arrival order
 - We often need to process some elements out of sequence
   * In a resturant customers who have a reservation are seated before customers
     without reservation
   * VIP's expect to go to the front of the queue!
 - This can be implemented using a priority queue
 - A priority queue is very similar to a queue
 - However, it orders its elements with the "most important" at the front and
 the least important at the back
 - C++ provides a priority queue
   * The < operator of the element type is used to order the queue
   * If the two elements have equal priority, by default the queue does not oder
   them by arrival time

----------------------------
Priority Queue Implementation
----------------------------
- std::priority_queue can be implemented as a vector or a deque
- It has a similar interface to std::queue
  * Use push() to add an element to the queue. It will be inserted in front of
    all the other elements with lower priority
  * pop() removes the element from the front of the queue. The element with the
    next highest priority becomes the new front element
  * top() returns the element with the highest priority
  * empty() returns true if there are no elements in the queue
  * size() returns the number of elements in the queue

----------------------------
Priority Queue Applications
----------------------------
- Priority queues are useful for processing data which needs to be prioritized
  * Operating system schedulers
    - Important processes can be given more processor time
    - Unimportant processes get less processor time
  * "out-of-band" communication in networking
    - e.g. command to drop the connection immediately
  * Management system for bug reports
    - Serious bugs should be fixed before minor bugs

---------------------------------
Priority Queue Pros and Cons
---------------------------------
- We can only access the "top" element
  * If you need access to the other elements, use a map instead
    - The map's key is priority, value is data
- Elements with the same priority are not guaranteed to be in arrival order
- If ordering by arrival time is important
  * Use a nested map
    - The outer map's key is priority
    - The inner map's key is arrival time, value is data
  * If we are using own class, redefine < operator

*/

#include <iostream>
#include <queue>

using namespace std;

void print(const priority_queue<int> &pq) {
  cout << "The queue is " << (pq.empty() ? "" : "not") << " empty\n";
  cout << "The queue contains " << pq.size() << " elements\n";
  cout << "The highest priority element is " << pq.top() << "\n";
}

int main() {
  priority_queue<int> pq;
  pq.push(4);
  pq.push(3);
  pq.push(5);
  pq.push(1);

  print(pq);

  // insert a new element in the queue
  cout << "\nAdding element with value 2\n";
  pq.push(2);
  print(pq);

  // remove the top element
  cout << "\nRemoving top element\n";
  pq.pop();
  print(pq);
}

/*
-------------
Stack
-------------
- A stack is a data structure in which elements are stored in the order in which
they are inserted
- When new elements are added to the stack, they are inserted at the top
- Only the element at the top can be accessed
- As a stack is processed, the element at the top is removed and the element
below it now becomes the top
- Elements are removed in the reverse order they were added
- This is a LIFO structure (Last In, First Out)

-----------------
Stack Operations
-----------------
- The C++ stack is implemented using deque
- std::stack has a similar interface to priority_queue
  * Use push() to add an element at the top of the stack
  * pop() removes the element from the top
  * top() returns the element at the top of the stack
  * empty() returns true if there are no elements in the stack
  * size() returns the number of elements in the stack

----------------------
Stack Applications
----------------------
- Stacks have many applications
  * Parsing expressions in compilers
  * Checking for unbalanced parentheses in source code
  * Implementing "undo" functionality
  * Storing history for back/forward buttons in web browser
*/

#include <iostream>
#include <stack>

using namespace std;

void print(const stack<int> &s) {
  cout << "The stack contains " << s.size() << "\n";
  cout << "The top element is " << s.top() << "\n";
  cout << "The stack is empty? " << boolalpha << s.empty() << "\n";
}

int main() {

  stack<int> s;
  s.push(1);
  s.push(2);
  s.push(5);

  print(s);

  cout << "\nAdding element with value 3\n";
  s.push(3);
  print(s);

  cout << "\nRemoving the top element\n";
  s.pop();
  print(s);
}

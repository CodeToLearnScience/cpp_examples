/*
-----------------------------------------------
Weak Pointer and Cycle Prevention
-----------------------------------------------
- This is the other main reason why weak_ptrs were added in C++11

--------------------------------
Cyclic References
--------------------------------
- Father and Son objects which have a shared_ptr to each other. And the
references count can never go down to zero. That means shared memory is never
released, and the destructors of the object are never called.

  struct Father{
    shared_ptr<Son> fptr;
  };

  struct Son{
    shared_ptr<Father> sptr;
  }

  shared_ptr<Father> father = make_shared<Father>();
  shared_ptr<Son> son = make_shared<Son>();
  father.set_son(son);

*/

#include <iostream>
#include <memory>

using namespace std;

struct Son;

struct Father {
  ~Father() { cout << "Father destructor\n"; }
  void setSon(const shared_ptr<Son> &s) { mySon = s; }
  shared_ptr<const Son> mySon;
};

struct Son {
  Son(const shared_ptr<Father> &m) : myFather(m) {}
  ~Son() { cout << "Son destructor\n"; }
  shared_ptr<Father> myFather;
};

namespace soln_with_weak_ptr {

struct Son;

struct Father {
  ~Father() { cout << "Father destructor\n"; }
  void setSon(const shared_ptr<Son> &s) { mySon = s; }
  shared_ptr<const Son> mySon;
};

struct Son {
  Son(const shared_ptr<Father> &m) : myFather(m) {}
  ~Son() { cout << "Son destructor\n"; }
  weak_ptr<Father> myFather;
};

void example() {
  // Now the Father's reference count it 1, When the Father's shared_ptr is
  // destroyed, the reference count will go to zero. That will call destructor
  // and release Father's memory. And the destructor will be again called for
  // son
  cout << "\n";
  {
    auto father = make_shared<Father>();
    auto son = make_shared<Son>(father);
    father->setSon(son);
  }
  cout << "\n";
}
} // namespace soln_with_weak_ptr

int main() {
  // when we get to the end of this scope, the destructor will be called for the
  // two shared_ptrs. The references counter is currently 2. And when scope
  // ends, that will decrement to 1 but doesn't go to zero. So the shared_ptr
  // does not release its memory, and it does not call the destructor
  cout << "\n";
  {
    auto father = make_shared<Father>();
    auto son = make_shared<Son>(father);
    father->setSon(son);
  }
  cout << "\n";
  soln_with_weak_ptr::example();
}

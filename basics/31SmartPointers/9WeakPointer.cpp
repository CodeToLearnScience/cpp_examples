/*
--------------------
Weak Pointer
--------------------
- A weak pointer is not a smart pointer but you can use then when you use
shared_ptr that's why discussing here
- It provides a safe way of aliasing a shared_ptr but not unique_ptr as they are
unique and there is only one object which can access the memory
- This avoids the problems with traditional pointers which can "dangle"

------------------------
std::weak_ptr
------------------------
- A weak_ptr is bound to a shared_ptr object
- This does not affect the reference count
- The weak_ptr cannot access the shared_ptr memory directly
- The only way that the weak_ptr can access the shared_ptr is to be converted
back to the shared_ptr (Its bit like doint cast) and this conversion is possible
only if the original shared_ptr is still valid
- This is only allowed if the shared_ptr is still valid

  auto ptr{make_shared<int>(36)}; //create shared_ptr object - its reference
                                  //count is 1

  weak_ptr<int> wptr = ptr;      //Create weak_ptr alias to ptr - reference
                                 //count is still 1

  ptr = nullptr;                 //release ptr's shared memory - reference
                                 //count is 0
- one we release the shared_ptr memory, we cannot do the conversion, so we
cannot use the weak_ptr


----------------------------------------
weak_ptr to shared_ptr
----------------------------------------
- The lock() member function returns the original shared_ptr if it is still
valid, otherwise it returns nullptr

  shared_ptr<int> sp1 = wptr.lock();
  if(sp1)
  ...

- Alternatively, we can copy the weak_ptr into a shared_ptr

  shared_ptr<int> sp2(wptr);

- This will throw std::bad_weak_ptr exception if invalid
- To prevent a data race, lock() is implemented as an atomic operation. So it is
thread safe but not very fast

-------------------------------
Weak Pointer Applications
-------------------------------
- Cache implementation (HTML Cache for ex)
  * Data stored in shared_ptr objects
  * Cache holds weak_ptr to data
  * Use lock() to retrieve data
  * original data returned if not expired
  * Otherwise, need to fetch again
*/

#include <exception>
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

namespace weak_ptr_ex {
void example() {
  auto ptr{make_shared<int>(36)}; // reference count is 1

  cout << "Shared ptr's data is " << *ptr << "\n";

  // create weak_ptr to ptr
  weak_ptr<int> wptr = ptr; // reference count is still 1

  // release ptr's shared memory
  ptr = nullptr; // ptr's reference count is 0

  // wptr is an alias to ptr - is it still valid?
  shared_ptr<int> sp1 = wptr.lock();

  // since we released the shared_ptr memory, we do not recover a valid
  // shared_ptr
  if (sp1) {
    cout << "Shared ptr's data is " << *sp1 << "\n";
  } else {
    cout << "shared_ptr not valid\n";
  }

  // we can try with exceptions as well
  try {
    shared_ptr<int> sp2{wptr};
    cout << "shared_ptr's data is " << *sp2 << "\n";
  } catch (exception &e) {
    cout << e.what() << "\n";
  }
}

// slighly interesting example with weak_ptr
void print(vector<shared_ptr<int>> vec) {
  cout << "Vector elements: ";
  for (shared_ptr<int> p : vec) {
    cout << *p << ", ";
  }
  cout << "\n";
}

void print_with_weak_ptr(vector<shared_ptr<int>> vec) {
  cout << "Vector elements: ";
  for (weak_ptr<int> p : vec) {
    auto ptr = p.lock();
    if (ptr) {
      cout << *ptr << ", ";
    } else {
      cout << "Deleted element, ";
    }
  }
  cout << "\n";
}
void interesting_ex() {
  vector<shared_ptr<int>> vec{make_shared<int>(36), make_shared<int>(42),
                              make_shared<int>(46), make_shared<int>(50)};

  print(vec);
  cout << "Deleting vec[2]\n";
  vec[2] = nullptr;
  // print(vec); // will result in seg-fault. So we need to check that the
  //  shared_ptr is valid before we dereference it. One way to do
  //  this is to use weak_ptr as the element type in the loop

  print_with_weak_ptr(vec);
}

} // namespace weak_ptr_ex
int main() {
  // create pointer
  int *ptr = new int(36);
  cout << "*ptr's data is " << *ptr << "\n";

  // create pointer which is an alias to ptr
  int *wptr = ptr;

  // release ptr's memory
  delete ptr;

  // how do we know if wptr is still valid?
  cout << "wptr's data is " << *wptr << "\n";
  cout << "--------------Weak Pointer-----------------\n";
  weak_ptr_ex::example();
  weak_ptr_ex::interesting_ex();
}

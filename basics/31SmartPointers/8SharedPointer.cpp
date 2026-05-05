/*
-----------------------
std::shared_ptr
-----------------------
- std::shared_ptr was introduced in C++11
- It uses reference counting
- This allows different shared_ptr objects to share a memory allocation
  * When a shared_ptr object is copied or asigned, there are no memory
    operations
  * Instead, the reference counter is incremented
  * When one of the shared_ptr objects is destroyed, the counter is decremented
  * When the last shared_ptr object is destroyed, the counter is equal to zero
  * The allocated memory is then released

----------------------------------
std::shared_ptr structure
----------------------------------
- shared_ptr has a private data member which is a pointer to the allocated
memory
- It has another private data member which is a pointer to its "control block"
- The control block contains the reference counter and few other things

               -------------------------
              |    Allocated Memory     |
              |                         |
              |                         |
              |      Control Block      |
               -------------------------
- shared_ptr is defined in <memory>
- To create a shared_ptr object, we can pass a pointer to its constructor, or
call make_shared()
- We can also initialize a shared_ptr by moving a unique_ptr into it
  * This transfers the owenership of the unique_ptr's allocated memory
  * Can be useful when working with factory functions which returns a unique_ptr
- However, we cannot convert a shared_ptr to unique_ptr
- Also, if you start writing a program using unique_ptrs, and you realize later
on that you actually need a shared_ptr then you can just convert them

-----------------------
Initialization
-----------------------
- make_shared() performs a single allocation for the shared memory and the
control block in one single contiguous block of memory

  auto p1{make_shared<int>(42)}; //available from C++11

- If we call new() to allocate the memory ourselves, the control block is
allocated separately
  * Extra call to new()
  * The shared memory and the control block are probably not contiguous

    shared_ptr<int> p1{new int(42)}; //less efficient - not recommended

--------------------
shared_ptr copyign
--------------------
- Copy constructor, assignment operator, and the move operators work just like
the example
  * shared_ptr<int> p2(p1);
- Before the copy, p1's reference counter had the value 1
- After the copy, p2's shared memory pointer and control block pointer will be
the same as p1's
- The counter in the shared control block will have the value 2

-------------------------
shared_ptr assignment
-------------------------
- Assignment
  p3 = p1; //where p3 and p1 have different pointer members
- The counter p1's control block is incremented
- The counter in p3's control block is decremented
- If this becomes zero, p3's shared memory will be released
- p3's shared memory pointer and control block pointer are now the same as p1's

----------------------------------
shared_ptr Move operations
----------------------------------
- When a shared_ptr is moved from, its memory allocation pointer is set to
nullptr

  shared_ptr<int> p4(std::move(p1));

- The value of its reference counter is unchanged
- The target object "steals" the memory allocation and the control block

----------------------------------------
shared_ptr and threads
----------------------------------------
- When different threads copy or assign shared_ptr objects which use the same
control block, there is a data race
- To prevent this, the reference counter is "atomic" so copying or assigning
shared_ptr objects is thread-safe
- However, accesses to the allocated memory must be protected by the programmer
  * C++20 has atomic shared_ptr typically by locking a mutex
- Operations on atomic variables take much longer, even in non-threaded code

---------------------------
shared_ptr vs unique_ptr
---------------------------
- unique_ptr has the same overhead as using a traditional pointer
- shared_ptr has more overhead
  * control block initialization
  * The reference counter needs to be updated (which is a slow operation) when
    copying, assigning or destroying an object.
- A unique_ptr can be converted to a shared_ptr, but not vice versa
- Only use a shared_ptr when needed
- Some people say that you should use shared_ptr all the time, that's true if
you are not worried anout efficiency

-------------------------------
Shared Pointer Applications
-------------------------------
- Shared pointers are useful where different objects need to have access to the
same area of heap memory
  * Duplicate words in large documents: we can save memory by storing them in a
    shared pointer
  * A web browser where several tabs are displaying the same image: we can save
    memory by storing the image in a shared pointer
*/

// shared_ptr supports the same observations as that of unique_ptr more or less
#include <iostream>
#include <memory>

using namespace std;

namespace shared_ptr_ex {
void example() {
  shared_ptr<int> p1{new int(32)};
  auto p2{make_shared<int>(42)};
  cout << *p1 << "\n"; // Single object can be dereferenced
  //++p1;                     // Error - pointer arithmetic not supported
  //++p2;                     // Error - pointer arithmetic not supported
  p1 = p2;                           // Ok - shared_ptr can be assigned to
  shared_ptr<int> p3(p2);            // Ok - shared_ptr can be copied
  shared_ptr<int> p4(std::move(p2)); // OK
  p1 = nullptr;                      // Calls delete on the pointer member
}

} // namespace shared_ptr_ex

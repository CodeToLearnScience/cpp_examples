/*
-----------------------
Smart Pointers
-----------------------
--------------------------------
Traditional Pointers
--------------------------------
- The "traditional" pointer was inherited from C
  * It is a built-in type
- A pointer variable stores a binary number which represents an address in
memory
  * Can represent the address of a stack variable (e.g function argument)
  * Can be used to manage memory allocated on heap (new/delete), typically for
    variable-lenth arrays
  * Can be used to implement polymorphism (Base *pb = new Derived); So when we
    call virtual functions through this pointer, we get the version from the
    derived class

----------------------------------
Drawbacks of Traditional Pointers
----------------------------------
- No concept of ownership
  * Any code that uses a pointer can reassign it, overwrite it or invalidate it
- No destructor
  * Allocated memory can be released twice, or not at all
- From C++11, traditional pointers are very rarely needed
  * For working with stack memory, we can use references instead of pointers
  * We can use std::vector instead of variable-sized arrays
  * We can use "smart" pointers for working with heap memory
  * For dynamic binding, we can use smart pointers or references

-----------------------------------
Smart Pointers
-----------------------------------
- Smart pointers are classes which encapsulate allocated memory
  * The class has a private data member which is pointer to the memory
  * The smart pointer object has ownership of the allocated memory
  * The allocated memory can only be accessed through public member functions
  * pointer arithmetic is not allowed
- Smart pointers are implemented using RAII
  * The memory is allocated in the constructor and released in the destructor
- Smart pointers save programmers a lot of work!
  * Both when coding and debugging

-----------------------
std::auto_ptr
-----------------------
- First attempt at a smart pointer appeared in C++98
- It transferred the allocated memory when copied
  * The copied-from auto_ptr object has its pointer set to null
- This caused problems for code which assumes that a copied-from object is still
valid
- Unpredictable behavior when auto_ptrs were stored in containers or used in
generic code. So this was a bit of a flop, really, and it was now been removed
from the language (C++14)

-----------------
std::unique_ptr
-----------------
- unique_ptr appeared in C++11
  * A better version of auto_ptr
  * The reason why it could not be done earlier, is because move semantics only
    came in C++11
- A unique_ptr object cannot be copied or assigned to
- However, the memory can be moved from one unique_ptr object to another

---------------------------------
std::unique_ptr vs std::auto_ptr
---------------------------------
- unique_ptr solves the problems with auto_ptr
- If we want to transfer the memory allocation, we have to do it explicitly
  * Use std::move()
- This makes it clear that the source object is now invalid
- We cannot accidentally transfer the memory
  * Code that tries to copy a unique_ptr will not compile

--------------------------
std::shared_ptr
--------------------------
- shared_ptr also appeared in C++11
- A shared_ptr object can share its memory allocation with other shared_ptr
objects. But is still encapsulated inside the class, and can only be accessed
via member functions
- References counting is used to manage the memory
  * The memory is only released when the last object which is using it is
destroyed
- Similar to a garbage-collected object in other langauges
- shared_ptr has more overhead than unique_ptr
  * It should only be used when the extra features are needed
*/

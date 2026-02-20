/*
------------------------------
Member Function Implementation
------------------------------
- Member functions are not stored in the object
- They are implemented as global functions
- When they are called, a pointer to the object is passed as an extra argument
called "this"

---------------------------------------
Virtual Member Function Implementation
---------------------------------------
- When the compiler encounters a class which has a virtual member function, it
creates and populates a data structure
  * This is the class's virtual member function table, known as its "vtable"
- When the compiler sees a call to virtual member function, it generates some
extra code
  * This code is executed at runtime
  * It checks the dynamic type of the object
  * It uses the vtable to call the correct version of the function

--------------------------------
Virtual Function Table (vtable)
--------------------------------
- The virtual function table stores the address of all the member functions of
the class which are declared virtual
- The vtableis an array of pointers to the class's virtual member functions
- Each virtual member function is identified by an index into the table

-----------------------------------
Virtual Function Call
-----------------------------------
- When a virtual member function is called, the compiler replaces the name of
the function by the corresponding index in the vtable
- THe runtime code will
  * Determin the object's dynamic type
  * Locate the vtable for that dynamic type
  * Look up the element in the vtable
  * Dereference the function pointer and call it

----------------------------------
Virtual Function Overhead
----------------------------------
- There is some overhead to using virtual member functions
- Efficiency
  * Calling a virtual member function takes longer than for non-virtual one
    about 20-50% more time
- Memory allocation
  * Each class that has a virtual member function needs a vtable
  * A pointer is needed for each virtual member function in the class
- Only use virtual member functions when the extra flexibility is required
*/

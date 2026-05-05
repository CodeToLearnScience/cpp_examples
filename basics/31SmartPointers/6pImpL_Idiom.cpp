/*
--------------------------
The PImpL Idiom
--------------------------
- There are a number of ways of implementing the Handle-Body pattern
In the PImpL idiom, the Handle has a private member which is a pointer to a
Body object
- "Pointer to Implementation" - pimpl
  * Also known as "compiler firewall" because it introduces a rigid separation
    between implementation code and client code

---------------------
Handle.h
---------------------
- Handle.h declares the Body class but does not define it
- Clients know only its name

  class Body; //Forward declaration of the Body class. So this means we do not
              //need to include the Body header in this Handle

  class Handle{
  private:
    Body* body; //pointer to implementation in Body class

  publib:
  //member functions to provide the interface
  void func(); //implemented as boyd->func();
               //These forward to Body's public member functions
  };

----------------------
pimpl and RAII
----------------------
- The Handle class is implemented using RAII
  * The Body object is allocated in the constructor
  * The Body object is released in the destructor
  * Need to consider the effects of copy and move operations

- Date_impl.H is going to be Body object
- 6a, 6b, 6c, and 6d shows the example of Handle-Body pattern

-------------------------
pImpl with unique_ptr
-------------------------
- We can use unique_ptr with pImpl idiom

  class Body; //Forward declaration of the Body class

  class Handle{
  private:
    unique_ptr<Body> body; //Pointer to implementation in Body class
  };

- However, this will not compile unless ~Handle() is declared
  * Needed to make Handle a "complete type"
- If we declare a destructor, the compile will not synthesize move operators
  * We need to provide these if we want them
- The compile will not synthesize copy operators
  * The unique_ptr member cannot be copied

-----------------
Pros and cons
-----------------
- Advantages
  * Clients do not need to include Body.h
  * Clients do not need to be modified if Body.h changes
  * Clients do not need to be recompiled if Body,h changes
  * Users do not need a new program executable if Body.h changes
  * Useful if implementation needs to be kept secret from clients

- Disadvantages
  * Requires an extra memory allocation for the Body object
  * Member functions calls requires a pointer dereference
  * Loading a shared library increases the program's start-up time
  * Adds complexity to the codebase

------------------------------
Applications of pImpl
------------------------------
- pimpl is often used in large projects, to reduce compilation time and simplify
product updates
- Heavily used in QT
- pimpl could be used to write standard contaier classes
  * std::string could have a body which stores the data and manipulates it, and
    a handle which provides the std::string interface
  * With careful programming, we could arrange for two string objects which
store the same data to share the same body pointer, saving memory
*/

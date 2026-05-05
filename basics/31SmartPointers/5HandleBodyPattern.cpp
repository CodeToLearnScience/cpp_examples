/*
-----------------------
The Handle Body Pattern
-----------------------
------------------------------------
Interface/Implementation Separation
------------------------------------
- In object-oriented programming, we aim to separate the interface from the
Implementation. One of the things we should do is to have a clear separation
between the interface to a class and its implementation details.
  * Clients do not need to know inner details of the class
  * Clients do not need to modify their code if the Implementation changes

Client --> Interface --> Implementation

- We have our class with its interface and implementation, and we have some code
which interacts with an object of this class. The code should only interact with
the interfae to the class. So by calling public member functions. And the actual
inner details of the class--the way the functions are implemented--the data
members of the class and so on should be completely hidden from the client. So
the interface acts as a kind of firewall, if you like, between the class
implementation and code that uses the class. The advantages of this is that even
if we change something in inner details of the class, the client code is not
affected. The only time we need to modify the client is if the interface changes

---------------------------------------------------
Interface/Implementation Separation in C++
---------------------------------------------------
- Typically in C++, we put the class definition in a header file and the member
function definitions in a source file. But this is not 100% proof.
  * public, private and protected specifiers are used to control access to the
    implementation
- However, some implementation details are still visible to clients
  * Names of private data members
  * Prototyes of private/protected member function
  * definitions of inline member functions (template member functions for ex)
- All clients which use the class must include the header file
  * Any implementation changes will force a recompile of all clients. And for
    large projects, this can be a big problem. The Handle-Body pattern was
    introduces to address this

-------------------------------
The Handle-Body pattern
-------------------------------
- We split class into two parts
  * The handle is an outer class that provides the interface to clients
  * The body is an inner class that provides the implementation
  * When a client creates a Handle object, the Handle creates a Body object
  * When a client calls a member function on the Handle object, the call is
    forwarded to the Body

    Client --> Handle (Interface) --> Body (Implementation)
- When the client calls a public member function in the handle, the handle will
forward that call to the same public member function in the body. If you know
about the "Adapter Design Pattern" then this is something similar. The Handle is
making the Body appear to be something else to the client. In this case the
Handle is making the Body appear as though it is not there. So as far as the
client is concerned, the Body is really a ghost
- Handle.h defines the Handle class
  * public member functions only
- Body.h defines the Body class
  * The full class defintion
- Clients #include Handle.h but not Body.h
- If the implementation details change, this only affects Body.h
- Clients do not need to be recomiled

-------------------------------------------------------
Compilation of Handle-Body pattern with Static linking
-------------------------------------------------------
- Body.h is only needed in Body.cpp. So we can do what we like with the Body
code, and the client will not need to be compiled. When we compile and link the
program, that will introduce the binary code for the Body into the program
binary. So the client code will be able to call the functions from the binary
object. This is so called "static" linking, in which all the binary code is
combined into a single binary. With the "dynamic" linking we can take this one
step further

Handle.h ──┬──> Client.cpp ──-┐
           │                  │
           └──> Handle.cpp ───┼──> [Compiler] ──> Client.exe
                              │
Body.h ────────> Body.cpp ────┘

---------------------------------------------------
Handle-Body with Shared library
---------------------------------------------------
- Body.cpp is compiled into a shared library, which is loaded to run time

Handle.h ──┬──> Client.cpp ──-┐
           │                  ├──> [Compiler] ──> Client.exe
           └──> Handle.cpp ───┘                        ^
                                                       : (dashed)
Body.h ────────> Body.cpp ──────> [Compiler] ──> Body.dll

- If you are company which is selling products and you have an update, bu you
have only changed the code in the Body - the implementation of this class then
you can just send your customers a new version of the DLL
*/

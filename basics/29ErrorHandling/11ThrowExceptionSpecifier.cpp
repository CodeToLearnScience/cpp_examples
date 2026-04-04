/*
-------------------------------
The no-throw Gurantee
-------------------------------
- The no-throw guarantee means that an operation will not throw an exception
- When writing code that provides the basic or strong guarantees, it is helpful
to know that a sub-operation will not throw
- None of the functions and operations in the core C++ language and library
throw exceptions, apart from:
  * new
  * dynamic_cast
  * throw

--------
throw()
--------
- C++98 provided the throw() exception specifier
- This comes after the function's parameter list
- The arguments list the exceptions that the function could throw
  //Function with an exception list
  //The function can throw NetworkConnectionError or DataError
  void func() throw(NetworkConnectionError, DataError){
    ...
  }
- If the function throws an exception which is not in the list, the program is
immediately terminated by default

-----------------------
throw() with Arguments
-----------------------
- An empty argument list indicates that the function does not throw any
exceptions
  //Function that does not throw exceptions
  void func() throw(){
    ... //No exceptions thrown here, honest!
  }

----------------------
Problems with throw()
----------------------
- The list of exceptions is not checked by the compiler
- If the list of exceptions is incorrect, the program may be terminated
unexpectedly

---------------------------
Removal of throw() from C++
---------------------------
- throw() has been removed from the language and replaced by noexcept
  * throw() was deprecated in C++11
  * throw() with an argument list was removed in C++17
  * throw() with an empty arguments list is removed in C++20
*/

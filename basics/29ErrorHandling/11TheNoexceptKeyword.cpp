/*
-----------------
noexcept keyword
-----------------
- C++11 has the noexcept keyword which replaces the old throw()
- This is equivalent to throw() with any empty list

  //Function that does not throw exceptions
    void func() noexcept{
      ... //No expcetions thrown here, honest!
    }
- If an exception is thrown, the program terminates immediately

--------------------------
The No-throw Guarantee
--------------------------
- noexcept is a promise to the caller that the function will not throw an
exception
- A noexcept function provides the no-throw guarantee
- This is helpful if we are writing exception-safe code which calls the function

-------------------------------------
Performance advantages of noexcept
-------------------------------------
- noexcept helps the compiler generate better optimized code
  * More information about how the code behaves
  * Not required to generate code for "stack unwinding"
- Modern C++ has optimized versions of some operators
  * These are not intrinsically exception-safe
  * Standard library algorithms will only use these operators if they are
declared noexcept
  * Otherwise they will call the non-optimized versions which are slower

-------------------------
When to use noexcept
-------------------------
- noexcept should be used wherever possible
  * If we are certain a function will not throw any exceptions
  * Or we cannot do anything useful if an exception is thrown (automatic
termination)
- Examples
  * std::swap() overloads
  * Destructors

-----------------------------
No overloading on noexcept
-----------------------------
- A function must either be noexcept or not be noexcept
  void func();
  void func() noexcept; //Error! cannot overload
- noexcept is part of the function's type, but is not part of the function's
signature
  * Similar to the return type

---------------------------
noexcept and inheritance
---------------------------
- "noexcept-ness" is inherited
  * If a virtual function is noexcept in the base class, overrides in the
    derived class must also be noexcept
  * Inheriting constructors will be noexcept if the base class constructor is
    noexcept
  * Synthesized special member functions will be noexcept if the base class
    version is noexcept
- A child can add "noexcept-ness", but no remove it
  * A virtual function in the base class which may throw can be overriden by an
    noexcept member function

----------------------------------
Destructors are implicitly noexcept
----------------------------------
- The compiler will assume a class's destructor is noexcept if
  * All members of the class have a noexcept destructor
  * All parent classes have a noexcept destructor
- This allows existing code to benifit from having "noexcept" destructors, with
  no modification
- However, it is better to write "noexcept" explicitly in new code
*/

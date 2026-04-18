/*
-----------------------
Move Semantics
-----------------------
- When we implemented swap() function, we saw that sometimes we can speed things
up by exchanging data instead of copying objects. For example, with the string
argument, we could just swap over the memory buffers which contain the data.
- Move Semantics is a bit like that, except it concerns function arguments and
function return values

-------------------
Value Semantics
-------------------
- C++ often uses value semantics, in which data is copied. Which means there is
a lot of data copying going on. For example, with function calls, by default,
arguments are passed by value, which means copying them and they are returned by
value, which again means copying them.
- STL containers copy data into their elements
  * Using reference is not allowed (too easy to create dangling reference)
  * Pointers can be used, but may dangle or cause memory leaks
- The reason why value semantics was chosen, was that it avoids the need for a
garbage collector.
- However, it requires copying objects
  * This increases the execution time
- To overcome this, traditional C++ can elide copies when returning temporary
and local variables from functions. And move semantics in Modern C++ is another
attempt. To understand how much time this can save consider the following code
executed in C++03
   vector<string> vec(1'000'000); //vector of 1 million strings
   ...                            //Populate vec
   func(vec);                     //Pass vec by value to a function
   ...                           //Vec is not used again
- The function call causes a new vector of 1 million strings (copy constructor)
to be allocated for the function argument
- And at the end of scope, when the variable is destroyed, there will be 1
million calls to the string destructor
- So if there was some way to get this data, the 1 million strings out of the
vector and into the function call argument, then we could save a lot of time and
Move Semantics for that

----------------------
Move Semantics
----------------------
- Consider how it could be executed more efficiently
   vector<string> vec(1'000'000); //vector of 1 million strings
   ...                            //Populate vec
   func(vec);                     //Move vec's data into the function argument
   ...                           //Vec is not used again

- The function call will not cause any allocation for the function argument
- The elements of vec are "moved" into the function argument
- At the end of this scope, vec's destructor will destroy the empty vector
- C++11 introduced move semantics
- This is an optimization over copying objects
- If the source object is an "rvalue", its data can be moved into the target
instead of being copied
- Similar to moving files between folders instead of copying them
*/

/*
---------------------
Value Categories
---------------------
- These are something which came in C++17, although they actually describe the
situation which goes to C++11

---------------------------
Characteristics of lvalues
---------------------------
- lvalues represent persistent objects
- These occupy memory which is acceptable to the programmer
  * Either on the stack or the heap
- They remain valid until they go out of scope or are deleted
  * Local variables
  * Global variables
  * Static variables
  * Function arguments

---------------------------
Characteristics of rvalues
---------------------------
- rvalues are stored in locations which are not accessible to the programmer,
such as processor registers
- Literals like 2 or 'c'
- Temporary objects
  * Destroyed in the same statement in which they are created

----------------------
Value Categories
----------------------
- C++17 has three "value categories" to describe these possibilities
- Literals
  * These have no name and cannot be referred to again
  * These are called pure rvalues or "prvalues"
- Temporary objects
  * These represent an object and their data can be moved
  * They are known as "xvalues" (x for "eXpiring"?)
- lvalues
- Every expression has a type and a value category

------------------------
Value Categories Diagram
------------------------

                    ┌─────────────────────────────────┐
                    │         rvalue                  │
                    │                                 │
        ┌─────────┐ │  ┌──────────────┐ ┌───────────┐ │
        │ lvalue  │ │  │   xvalue     │ │ prvalue   │ |
        │         │ │  │              │ │           │ |
        └─────────┘ │  └──────────────┘ └───────────┘ │
                    │                                 │
                    └─────────────────────────────────┘

- In fact, that is not quite the end of the story
- lvalues and xvalues are objects
- Their dynamic type can be different from their static type
- They are collectively known as "generalized lvalues" or "glvalues"

------------------------------------------
Final version of value categories
------------------------------------------

        _________ glvalue _________        _________ rvalue _________
       /                           \      /                           \
      /   (lvalue)                 \____/                 (prvalue)   \
     /                             / x  \                             \
     \                            /value \                            /
      \                          /       \                          /
       \________________________/         \________________________/

The diagram shows how C++ value categories relate to each other using a
Venn-style layout.

There are two main groups:

- glvalue (left): expressions that have identity (you can refer to a specific
object)
- rvalue (right): expressions that can be moved from (temporary or expiring
values)

Inside these:

- lvalue is entirely within glvalue — these are named, stable objects
with identity.
- prvalue is entirely within rvalue — these are pure temporary values (literals)
without identity.

The overlap between glvalue and rvalue contains xvalue:

xvalue represents objects that still have identity (like glvalues) but are
about to be moved from (like rvalues).

In short:

* `lvalue ⊂ glvalue`
* `prvalue ⊂ rvalue`
* `xvalue ⊂ (glvalue ∩ rvalue)`


*/

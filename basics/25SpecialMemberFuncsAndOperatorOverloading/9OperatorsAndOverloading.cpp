/*
 - Operations which take single argument are member functions and are called
   unary operators
 - Operations which take two arguments are non-member functions and are called
   binary operators
 - And - (minus) operator can be both. One as binary operator which takes two
   objects and subtracts them and other takes one object and negates that
 - There is one ternary operator as well
   a ? b : c;
*/

/*
 - Overloading operator means giving different meaning for different arguments
 - We can only use the symbols which are supplied for built-in operators, and
   we have to use the same
*/

/*Useful operators to overload
  - The +, -, * and / operators are only really useful for mathematical classes
    (complex numbers, rational numbers and so on...)
  - In general programming, the most useful operators are
    * Assignment operator =
    * Equality operator ==
    * Inequality operator !=
    * Less than operator <
    * Function call operator ()

- Opearators which should not be overloaded
  * Logical AND and OR (&& and ||)
  * Address-of (&) and comma (,)
  * Scope (::), .operator, .* operator and ternary operator (?:)
*/

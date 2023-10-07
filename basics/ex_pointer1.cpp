#include <iostream>

int main()
{
  int i1 = 9;
  int *p_i1 = &i1; //creating pointer which points to the address of i1

  std::cout << "print the pointer, *p_i1 value = " << *p_i1 << std::endl; //* is dereference operator

  //we can also assign value to pointer
  *p_i1 = 18;
  std::cout << "print the pointer, *p_i1 after assigning a new value = " << *p_i1 << std::endl;
  std::cout << "print the value of original object, i1, to which pointer points to  = " << i1 << std::endl;

  //meaning of different symbols

  int i = 42;
  int &r = i;   // &follows a type and is part of a declaration; r is a reference
  int *p;       // *follows a type and is part of declaration; p is a pointer
  p = &i;       // &is used in an expression as the address-of operator
  *p = i;       //* is used in  an expression as the deference operator
  int &r2 = *p; // & is part of the declaration; * is the dereference operator

  /*In declarations, & and * are used to form compound types. In expressions
    these same symbols are used to denote an operator. */

  /////////////////////////////////////////////////////////
  //creating null pointer

  int *p1 = nullptr; //equivalent to int *p1 = 0
  int *p2 = 0;       //directly initializes p2 from the literal constant 0
  //must #include cstdlib
  int *p3 = NULL; //equivalent to int *p3.

  //illegal to assing int to pointer

  //assignment and pointers
  /* //////////////////////////////////
     1. Both pointers and reference gives indirect access to other objects.
     2. Reference is not an object. When we use a reference, we always get 
     the object to which the reference was initially bound.
     3. There is no such identity b/w a pointer and the address that it holds
     */

  int *pi = 0;   // pi is initialized but addresses no object
  int *pi2 = &i; // pi2 is initialized to hold the address of i
  int *pi3;      //if pi3 is defined inside a block,pi3 is uninitialized

  pi3 = pi2; //pi3 and pi2 address the same object, e.g., i
  pi2 = 0; // pi2 now address no object

  // keep in mind that assignment changes its left-hand operand

  pi = &i1; // value in pi is changed; pi now points to i1

  *pi = 0; //value in i1 is changed; pi is unchanged

  //void* pointers
  //special pointer type that can hold the address of any object

  double obj = 3.14, *pd = &obj;
  //ok; void* can hold the address value of any data pointer type
  void *pv = &obj; //obj can be object of any type
  pv = pd; //pv can hold a pointer to any type

  return 0;
}

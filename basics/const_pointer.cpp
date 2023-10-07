#include <iostream>
#include <stdio.h>


int main(){

  int errNumb = 0;
  int *const curErr = &errNumb; //curErr will always point to errNumb
  const double pi = 3.14159;
  const double *const pip = &pi; //pip is a const to a const object

  // *pip = 2.72; //error: pip is a pointer to const
  //if the object to which curErr points (i.e., errNumb) is non zero
  if(*curErr){
    //errorHandler(); //some error handler
    *curErr = 0; //ok: reset the value of the object to which curErr is bound
  }

  //we use the term top-level const to indicate that the pointer itself is a const. 
  //when a pointer can point to a const object, we refer to that const as a low-level consta

  int i = 0;
  int *const p1 = &i; // we can't change the value of p1; const is top-level
  const int ci = 42; // we cannot change ci; const is top-level
  const int *p2 = &ci; //we can change p2; const is low-level
  std::cout << "p2 = " << *p2 << std::endl;
  const int *const p3 = p2; //right-most const is top-level, left most is not
  const int &r = ci; //const in reference types is always low-level
    
  /*the distinction btw top-level and low-level matters when we copy an object
   * When we copy an object, top-level consts are ignored.*/
  
  i=ci; // ok: copying the valuse of ci; top-level const in ci is ignored
  p2 = p3; // ok: pointed to type matches; top-level const in p3 is ignored

  std::cout << "p2 = " << *p2 << " " << *p3 << std::endl;
    
  /*low-level const is never ignored. when we copy an object, both 
   * objects must have the same low-level const qualification or 
   * there must be a conversion btw the types of the two objects
   * */

  int *p = p3; //error: p3 has a low-level const but p doesn't
  p2 = p3; //ok: p2 has the same low-level const qualification as p3
  p2 = &i; //ok: we can convert int* to const int*
  int &r = ci; //error: can't bind an ordinary int& to a const int object
  const int &r2 = i; //ok: can bind const int& to plain int 


  return 0;
}

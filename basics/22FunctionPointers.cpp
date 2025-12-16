/* 
----------------
Function pointer 
----------------
- A function's executable code is stored in memory 
- We can get a pointer whose address is the start of this code 
  
  void func(int, int); 
  auto func_ptr = &func; //deduces to: void(*func_ptr)(int, int)=&func 
- the actual type of the this pointer is rather ugly as we can see. It is 
  declared as a pointer and because of the operator precedence rules in C++, we 
  have to put it inside brackets. Without brackets it would be interpreted as a 
  function that returns pointer to void 
- func_ptr is a pointer to the function. Generally working with function pointer 
  types is pretty ugly. We can avoid it in the declaration by using auto, but 
  you might need it in other places as well. So its a good idea to use type 
  alias 

  using pfunc = void(*)(int,int); 
 
---------------
Callable Object
--------------- 
- A function pointer is a "callable object" 
  * Behaves like a variable 
  * Can be called like a function 
  * its kind of hybrid between data and code. We can copy it, we can pass it 
    around 
- We can call the function by dereferencing the pointer 
     (*func_ptr)(1,2); 
- A function pointer is a "first class object"
  * we can pass a function pointer as argument to another function 
  * we can return a function pointer from a call to another function 

--------------------------
Passing a function pointer
-------------------------- 
- We can pass a function pointer as an argument to another function 
  * void some_func(int, int, pfunc); 

- The function can all the pointed-to function in its body 
  voud some_func(int x, int y, pfunc func_ptr){
    (*func_ptr)(x,y);
  }

- We can return a function pointer from a function call 
  pfunc other_func(...);

----------------------------------
Pros and Cons of Function Pointers
---------------------------------- 
- Function pointers were inherited from C 
- Useful for writing callbacks 
  * operating systems, GUI's, event-driven code 
  * provide a function that will be called when "something" happens 
  * for example, if the user clicks on a button, you can ask them to call this 
    function, which will open a new window or something like that 
- "Raw" Pointers  
  * They can be overwritten by another function of same type. They can set to 
    null and they can be uninitialized. So there's quite a bit of scope for 
    problems here. Fortunately they don't involve memory management! And also 
    the syntax is pretty ugly. So there are better ways of doing these in C++
*/


#include <iostream> 

using namespace std; 

void func(int x, int y){
  cout << x << " + " << y << " = " << x + y << endl; 
}

using pfunc = void(*)(int, int); //The * is not optional!  
//typedef void(*)(const string&, const string&) pfunc; //older c++  


void some_func(int x, int y, pfunc func_ptr){
  (*func_ptr)(x,y); //The * is optional 
}

pfunc other_func(){
  return &func; //return a pointer to function func
}

int main(){
  
  auto func_ptr = &func; //The & is optional 

  (*func_ptr)(1,2); 
  //func_ptr(1,2); //The * is optional
  
  //we can return a function pointer from a function call 
  auto func_ptr1 = other_func(); 

  //passing func_ptr as an argument to another function 
  some_func(1, 2, func_ptr);

}

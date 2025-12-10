/*
 - casting performance an explicit conversion 
 Different purposes 
  - convert an expression to different type 
  - convert a const-expression to a non-const equivalent //came from C  
  - convert data in a buffer to untyped binary data. For example when you want 
    to send data in network which knows nothing about C++ types. 
  - convert pointer to a base class into a pointer to a derived class 
- Casting is rarely necessary in well-written C++ code, if you do, it is often 
   a sign that something "suspiciuos" is going on 
- you might need occasionally when interacting with C or other code 

C++98 casts 
  - four new ways of casting an expression 
    * one for each use 
  - These have very distinctive syntax 
    * (Type)expr 
    * Becomes xyz_cast<Type>(expr) 

*/


#include <iostream>

void print(char *str){ //doesn't mutate str - should have been const char* 
  std::cout << str << std::endl; 
}


int main(){

  //C-stype cast 
  //The c-style cast puts the type in parantheses
  int c='A';
  std::cout << c << std::endl; //prints 65 
  std::cout << (char)c << std::endl; //prints 'A' //you might miss reading char while reading code

  //1. static_cast is used to convert an expression to a different type 
  //there is no chance you could miss this when you are scanning through code
  std::cout << static_cast<char>(c) << std::endl; 

  //const-char 
  //2. const_cast is used to convert a const expression to the non-const equivalent 
  //may be needed to call functions that aren't const-correct (old or badly written code) 
  const char *msg = "Hello, world!";
  //print(msg); //error invalid conversion 
  print(const_cast<char *>(msg)); //cast to non-const. Generally a bad thing to do 

  /*3. reinterpret_cast 
    - is used to convert data in a buffer to untyped binary data 
    - Mainly used in low level work (communication with hardware, OS, binary files) 
  
    4. dynamic_cast 
    - is used to convert a pointer to a base class object to a pointer to derived class object 
    - also works with reference 
    - unlike the other types, it is done at runtime 
  */

  return 0;
}

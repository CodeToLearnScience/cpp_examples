#include <stdio.h>
#include <vector>
#include <string> 

int main(){
   /*
   ARRAY
  //an indexed block of contiguos memory 
  //inherited from C 
  //it can be allocated on program stack..only if the number of elements is
  //fixed and known at compile time 
  //gets destroyed at the end of scope 
  */
  int array[10];

  //Not allowed in standard C++ for variable nElements
  //Althouhg GNU C++ allows, so you need to turn it off pedantic
  //It's allowed in C though which is bit of hack so C++ hasn't adopted it
  int nElements;
  int array1[nElements]; 
  //So we need dynamic array for that. 
  int* dArray = new int[nElements];
  
  delete[] dArray;

  /*
    C-style strings
    - C-style string is an array of const char 
    - each character of the string is stored in an element in the array 
    - The array has a null extra character at the end to detect the end of the string
    - null character has the value 0. Not the character zero, the actual number value zero 
    - String literals are C-style strings
    - If you use c functions to manipulate these, it will look for the terminating null. 
      So they are slow as they have to look all the way for null 
  */
  //C-style string. Array will be allocated for us.
  const char *str = "hello"; //equivalent to const char str[] = {'h', 'e', 'l', 'l', 'o'} => |h|e|l|l|o|\0|
  
  /*
  String in C++ 
  - std::string is a class. Part of the C++ library, not the core language
  - It has a member which is a dynamic array 
  - It also has a member which stores the number of elements in a array 
  - Its a kind of object oriented string, as opposed to the procedural string in C 
  */
  class string{ //std::string 
    char *data;  
    size_t n;
    //...
  };
  
  /*
    - std::string objects behave like a dynamic array, but are used like a local variable 
    - contiguos block of memory allocated on heap in constructor 
    - released in destructor at the end of scope 
    - correctly handles copying and assigning objects, by allocating a new block 
    - Automatically reallocates the memory block when needed when change the size of string like hello world from hello 

    std::string interface 
    - subscript notation [] is supported 
    - Elements are indexed, starting from 0 
    - size() member functon returns number of elements 
  */
  std::string str{"Hello"};//allocates storage on heap and populates it 

  /* 
    std::vector 
    - similar to std::string, but can store data of any single type, in string it has to be characters 
    - type goes in <here> 

    std::vector interface 
    - subscript notation is supported [] 
    - Elements are indexed, starting from 0 
    - size() member function returns number of elements 
    - push_back() member function adds new element at the back of the vector 
  */
  std::vector<int> vec{1,2,3}; //vec of int 
  vec.push_back(6); 
  //similar to string its implemented as a class in standard library 
  class vector<int>{
    int* data;
    size_t n;
  };



  return 0;
}

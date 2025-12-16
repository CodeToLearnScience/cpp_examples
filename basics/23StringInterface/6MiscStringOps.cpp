/* -----------------------------
Miscellaneous String Operations
--------------------------------
----------------------
data() member function
----------------------
- std::string and std::vector have a data() member function 
- We know that the string has a pointer to a buffer containing the actual 
  characters. When we call the data member function, it returns a pointer to 
  the start of this memory buffer
  - For std::string, this is null-terminated 
    * Equivalent to c_str()
- if you have to work with code written in C. Maybe an OS API, or some library 
  or some old code that you are converting, then you don't have to use arrays 
  and pointers in your C++ code. You can use string and vector, and then 
  convert the results when you need to interact with C code. 
  
*/ 

#include <iostream> 
#include <vector> 

using namespace std; 

void print(int *arr, size_t size){
  for(int i=0; i<size; ++i){
    cout << arr[i] << ", ";
  }
}

int main(){
  vector<int> vec{1,2,3,4,5}; 
  print(vec.data(), vec.size());

/*-----------
Swapping 
------------- 
- std::string and std::vector has a swap member function. When we call this,
  it is going to swap the data of the two string objects. 
- There is also a non-member swap function 
  swap(s1, s2); 
- This global function has overloads for all the built-in and library types 
*/
  string s1{"Hello"};
  string s2{"Goodbye"}; 
  cout << "\ns1: " << s1 << ", s2: " << s2 << endl; 

  //call swap member function 
  cout << "calling the swap member function " << endl; 
  s1.swap(s2); 
  cout << "s1: " << s1 << ", s2: " << s2 << endl; 

  //calling the non-member function swap 
  cout << "calling the global swap function " << endl; 
  swap(s1, s2); 
  cout << "s1: " << s1 << ", s2: " << s2 << endl; 

  /*---------------------------------------------------------------------------
  Default implementation of swap() 
  ----------------------------------------------------------------------------- 
  - If there is no overload for a class, the default implementation of swap is 
    called 
  - This uses a temporary object 
    Obj temp = obj1; //copy constructor call 
    obj1 = obj2; //Assignment operator call 
    obj2 = temp; //Assignment operator call 
  - For simple objects, where copying is trivial operation, the above one is 
    fine but for something like string  
      * For std::string this would be a slow and inefficient operation 
      * Each operation requires all the data in a string to be copied
        - data in the string on the right to be copied in to the string on the 
          left. So that's one processor instruction per character in the best 
          case depending on where it is in memory. 
      * copy constructor will cause a memory allocation 
        - If the buffer in one of these strings is not big enough to hold the 
          data from the other object, then it will need to allocate a new buffer 
          and release the old one. And memory operations are very slow. In any 
          case copy constructor will need to allocate some memory because it is 
          creating a new object. This could be expensive 
      * The Assignment operations may cause a memory allocation 
  -----------------------------------
  Specialized swap() for std::string 
  ----------------------------------- 
  - This is how string is structured in memory 
    s1 => |5|.| -> |H|e|l|l|o| 
    s2 => |7|.| -> |G|o|o|d|b|y|e| 
    * It has a header with element count and pointer to the data. And then 
      actual characters in memory buffer which header points to 
  - However, the string overload does not do that. Bit more clever. It knows 
    what a string is and what string does 
  - Instead of copying data in and out of these buffers and allocating buffers 
    why not just swap around the headers. So s1 will get a header which has the 
    element count for "Goodbye" and a pointer to the data and s2 ends up with a 
    header which has the element count for "Hello" and points to the data with 
    "Hello" 

    s1 => |5|.|  |H|e|l|l|o| 
               \/
               /\
    s2 => |7|.|  |G|o|o|d|b|y|e| 
  - So advantage of this is there aren't any memory allocation or release 
    operations and none of the actual character data is copied. The only thing 
    that gets copied is the count and the pointer in the header 
  - The std::string class has a "header" 
    * integer with the character count 
    * Pointer to the character data 
  - The library implementation of swap reassigns the headers 
    * No memory operations 
    * No copying of data 
    * Only that gets copied is the count and the pointer in the header 

    //Pseudo=code 
     header temp=s1.hdr; //pointer assignment + integer assignment 
     s1.header = s2.hdr; //pointer assignment + integer assignment 
     s2.hdr = temp;      //pointer assignment + integer assignment 
  */
}

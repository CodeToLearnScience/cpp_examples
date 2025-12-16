/*C++ standard library string class 
- This class is unusual and it doesn't quite fit in with other containers in 
  C++ because string class was originally designed in isolation based on 
  various other classes that people hacked as there was no string class in C++ 
- Then standard template library came along, then they thought, its good idea 
  to make the interface for the standard string consistent with the interface 
  for containers in the standard template library. So the string actually has 
  two interfaces: its own native interface and the STL container and the result 
  of this is that it has very big interface. Over 100 member functions 

-------------------------------------------------------------------------------
Basic String Operations
-------------------------------------------------------------------------------
- Assignment 
  s1=s2; //s1 will have the same data as s2 
         //Also works if s2 is C-style string 

- Appending 
  s1+=s2; //s2's data will be added at the back of s1 
          //Also works if s2 is C-style string or char 

- Concatenation 
  s1+s2; //Returns new object containing s1's data followed by s2 
         //Also works if either s1 or s2 is C-style string or char 

- Comparsion 
  s1 cmp s2; //whre cmp is one of ==, !=, <, >, <=, >= 
             //Also works if s2 is C-style string or char  

  -modifying a C-style string is pain, especially if it is on the stack. So 
    this string library is useful in those cases as well 

-------------------------------------------------------------------------------
Compatability with C-syle string 
-------------------------------------------------------------------------------
- You might have to deal with code which either interfaces with C, for example 
  on OS or database or some third party library and since C++ provides a member 
  function c_str() which lets you convert a standard string to a C-style string 

  * This c_str() returns a copy of the string's data as a C-style string, i.e.,
    array of char terminated by null character 
  * this is returned as a pointer to const char 
      const char *pChar = str.c_str(); 
  * This is useful for passing C++ strings to functions that take C strings 

-------- 
substr() 
-------- 
- The substr() member function returns a substring. The substring starts at the 
  index corresponding to its argument 

  string str{"Hello world"}; 
  s1 = str.substr(6); //return "world" 

- By default, substr returns everything to the end of the string. We can change 
  this by giving second argument 
  s2 = str.substr(6,2); //returns "wo" 

------------------------
Constructors
------------------------
- Default constructor 
  string empty; //creates a string object with no data 

- Constructor with a string literal 
  string hi{"Hello"}; //"Hello" 

- Constructor with a count and an initial value 
  string triple_x{3,'x'}; //creates a string object with data "xxx" 

- Constructor with an initializer list 
  string howdy{'H', 'e', 'e', 'l', 'l', 'o'}; //Creates a string object with data "Hello" 

- We can also initialze a string variable from a substring. We don't need to call  
  the substring member function directly. We can just give the string and the 
  index 
  string hello1(hi, 1); //"ello" 
  string hello2(hi, 1, 3); //"ell" 
*/

#include <iostream> 
#include <string> 


int main(){
  std::string str{"Hello world"}; 
  str[1] = 'a'; //change 2nd character to 'a' 

  std::string s1 = str.substr(6); 
  std::string s2 = str.substr(6,2); //returns "wo" 

  std::cout << str << std::endl; 
  std::cout << s1 << std::endl; 
  std::cout << s2 << std::endl; 

  //default constructor 
  std::string empty; 
  std::cout << "empty has " << empty.size() << " characters: " << empty << std::endl; 

  //c-style string 
  std::string hi{"Hello"}; 
  std::cout <<"hi has " << hi.size() << " characters: " << hi << std::endl; 

  //repeated value 
  std::string triple_x(3, 'x'); 
  std::cout << "triple_x has " << triple_x.size() << " characters: " 
    << triple_x << std::endl; 

  //initialzer list 
  std::string howdy{'H', 'e', 'l', 'l', 'o'}; //Creates a string object with data "Hello" 
  std::cout << "howdy has " << howdy.size() << " characters: " << howdy << std::endl; 
}

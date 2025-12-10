/* 
- "auto" was originally used in C to specify that a variable should be created 
  on stack 
- In modern C++, it is used to indicate that the compiler should deduce the 
  type from the variable's initial value 

  auto i{42}; //equivalent to int i=42
  auto str1="Hello"; //equivalent to const char str1[]="Hello" 
  auto str2="Hello"s; //equivalent to std::string str2{"Hello"} 

- auto is useful for simplifying complex types 
  //write out iterator type in full 
  vector<int>::iterator it = vec.begin();
    
  //let the compiler deduce type 
  auto it=vec.begin();

- sometimes for example in template programming, it is not easy to work out the 
  type and to type it accurately, so auto will save us there 
- In modern c++, there are even situations in which it is impossible to know 
  what the type is! So the compiler can actually create classes which have a 
  type which is defined by the compiler and so using "auto" is the only way

auto with qualifiers
- auto will only give the underlying type 
- const, reference, etc are ignored
- it doesn't perform any kind of temporary objects or type conversion
- So it literlly just give the type that's required to make the initalizer work 

  let's say 
  const int& x{6};
  auto y=x;
  ++y; //is this allowed? yes as auto y=x reduces only type and const reference 
  is ignored, if we need const reference, we must add it like 
  const auto& y=x; //equivalent to const int& y=x; 

  const int& x{6}; means “x is a read-only reference to the number 6.”
  Reference: A reference is like a nickname for a value; it doesn’t make a copy.
  const: Read-only. You can look at the value through x, but you can’t change it.
  Why it works: Normally, references need a real variable, but const 
    references can bind to temporary values like 6. C++ keeps that temporary 
    alive as long as x exists.
  
  Quick feel:
    You can do: int y = x; (read the value: 6)
    You cannot do: x = 7; (won’t compile, x is const)
    Think of it as: “Create a stable, read-only handle to 6 without copying.”

 WHEN TO USE AUTO? 
 - use auto when the type doesn't matter, for example, if the type is not 
   interesting or doesn't matter at all. 
  - if the type doesn't provide any useful information to the person reading code 
  - generally best time to use auto is when it makes the code clearer. when the 
  code is clearer without type 
    ex. auto it = vec.begin(); //clearer than vector<int>::iterator it=vec.begin(); 
  - When the type is difficult to discover 
    - for example in template metaprogramming 
  - when the type is unknowable 
    - compiler-generated class
 DON'T USE AUTO 
  - if you want a particular type 
  - if it makes the code less clearer 
    ex: auto h = xyz(); //what does h represent?
*/

#include <iostream>
#include <string>


//we can also use auto to capture the value returned by a function 
int func(){ //function returning reference to const int 
  return 5;
}
using namespace std;
int main(){
  
  auto i{42}; //equivalent to int i=42
  auto str1="Hello"; //equivalent to const char str1[]="Hello" 
  auto str2="Hello"s; //equivalent to std::string str2{"Hello"} 
  
  std::cout << "i*2= " << i*2 <<"\n";
  auto it = str2.begin();
  std::cout <<"the first element: " << *it << "\n";

  const int& x{6};
  auto y=x;
  ++y; //is this allowed?
  //works becuase y is not const, its just a normal int so you can do ++y 
  //const auto& y=x; //not allowed 
    
  std::cout << "x= " << x <<"\n"; 
  std::cout << "y= " << y <<"\n"; 

  auto l=func(); //l has type int 
 return 0;
}



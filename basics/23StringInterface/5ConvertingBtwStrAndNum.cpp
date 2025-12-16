/* Converting between strings and numbers 
- C provided the functions atoi(), atod(), etc for converting C-style strings 
  to numbers 
- C does not provide anything for converting numbers to strings, although you 
  can use sprintf. That's bit clumsy, no many vendors provide non-standard 
  functions like iota for converting ints to strings. 
- These above are inherited by C++ 
- But C++11 provides to_string()
  * Returns its argument as an std::string 
  * There are overloads which will take any numeric built-in type. And they 
    will return the argument as a standard string 
*/ 


#include <cstddef>
#include <iostream> 
#include <string>

int main(){
  std::string pi{std::to_string(3.14159)};
  std::cout << "pi: " << pi << std::endl; 
  //to show that its a string 
  std::string hello{"Hello, "}; 
  hello+=pi; 
  std::cout << hello << std::endl; 

  /*----------------------------
  converting strings to integers 
  ------------------------------
  - stoi() takes an std::string argument and returns it as an int 
  */ 

  std::string str1{"42"}; 
  std::cout << std::stoi(str1) <<std::endl; 

  //Leading whitespace is ignored. Also, if it reaches something which is not a 
  //numeric character like space after 314, it will stop there and return only 314 
  std::string str2{"  314 159"}; //two leading whitespaces 
  std::cout << "string to int with leading whitespace: " << std::stoi(str2) << std::endl; 

  /*-------------------------
    Error Handling 
    ------------------------- 
    - An optional second argument gives the number of characters which were 
      processed 
    - If there is no error, this is equal to the strings size 
    - If the conversion is partially successful, this gives the index of the 
      first non-numeric character 
    - If the conversion fails completely, it throws an exception 
      stoi("adkjsk"); //cannot be converted-throws exception 
  */
  std::size_t n_processed; 
  auto i=std::stoi(str2, &n_processed);
  if(n_processed < str2.size()){
    std::cout << "non-numeric character at index " << n_processed << std::endl;  
  }
  std::cout << "Result of conversion: " << i << std::endl; 
  
  //std::cout << std::stoi("fkadjl") <<std::endl;//throws exception as it can't be converted 
  /*----------------------
    Base conversion 
    ----------------------
  - The string is assumed to be decimal by default, i.e., number with base 10
  - To specify different base, there is an optional third argument that gives 
    the base
      * Base can be anything between 0-36
        - not sure what's the use of base 0
      * Digits can be 0-9, A-Z or a-z 
        - If you have numbers with base 36, you can go all the way up to z 
  - If we are not using the second argument--if we don't care how many characters 
    were processed--we can just set that to null pointer
  */
  //convert string to hexadecimal 
  std::cout << "Converting to hexadecimal: " << std::stoi("2a", nullptr, 16) << std::endl; //42

  //There are other functions like std::stoll which will convert to long long 
  //and other built-in types 

  /*------------------------------------
    converting strings to floating-point
    ------------------------------------
    - stod() returns double
    - There is no option to use different bases 
      * Similar functions for float and long double 
    */
  
  //with std::stoi, '.' will be recognised as non-numeric and coversion will stop 
  //but with std::stod '.' will be recognised as part of flaoting point number 
  //You can have exponents as well 
  std::cout << "string to double: " << std::stod(pi) << std::endl; 
  std::cout << "the above one if used with stoi: " << std::stod(pi, &n_processed) << std::endl; 
  std::cout << "number of characters processed when used with stod: " << n_processed << std::endl;
}

/*  
Searching in strings 
---------
find() 
--------- 
- The find() member function looks for the first occurence of its argument in 
  the string. The search is case sensitive 
- The argument to these member functions can be a char, a std::string or a 
  C-style string 
- It returns the index of the first match 
- If there is no match, it returns string::npos 
  * This represents an impossible index (kind of not possible) 

  string str{"Hello world"}; 
  str.find('o'); // returns 4 
  str.find("or"); //returns 7 
  string.fin('O'); //returns string::npos 


*/ 

#include <iostream> 
#include <string> 


using namespace std; 

int main(){

  string str{"Hello world"}; 

  size_t pos=str.find('o'); 
  
  if(pos!=string::npos){
    cout << R"(First occurance of 'o' is at index )" << pos << endl; 
  }
  else{
    cout << R"(Could not find 'o' in the string)" << endl; 
  }

  pos=str.find("or"); 

  if(pos!=string::npos){
    cout << R"(First occurance of 'o' is at index )" << pos << endl; 
  }
  else{
    cout << R"(Could not find 'o' in the string)" << endl; 
  }


  pos=str.find('O'); 
  
  if(pos!=string::npos){
    cout << R"(First occurance of 'o' is at index )" << pos << endl; 
  }
  else{
    cout << R"(Could not find 'o' in the string)" << endl; 
  }
  
//----------------------------
// Checking return values 
//----------------------------
//We can use the return value from find() as an index, but we must first check 
//it is valid 
  pos = str.find('o'); // search for 'o' in str 
  if(pos!=string::npos){ //is the index valid 
    str[pos]='p'; // we know it is safe to access the element 
  }
  else{//search was not successful 
    cout << "Could not find the search string\n"; 
  }
  cout << "The modified string is: " << str << endl; 

/*-------------------
  rfind() 
  - Reverse find 
  - There is an rfind() member function that finds the last occurence of its 
    argument 
    string str{"Hello world"}; 
    str.rfind('o'); //returns 7
    str.rfind("or"); //returns 7 
  - By default, the search starts from the end of the string. We can change this 
    by passing a second argument 
    //search backwards starting from element with index 5. It starts searching  
    from space after w from backwards. Because 5 is the index of space 
    str.rfind('o', 5); //returns 4  
*/ 


  pos = str.rfind('o');  
  if(pos!=string::npos){  
    str[pos]='z'; // we know it is safe to access the element 
  }
  else{//search was not successful 
    cout << "Could not find the search string\n"; 
  }
  cout << "The modified string is: " << str << endl; 

/*----------------------------------------------------------------------------- 
More search functions 
----------------------------- 
- We can also search for one of a group of characters. 
- find_first_of and find_last_of search for the first (last) occurance of any 
  character from the argument string 
  string str{"Hello world"}; 
  string vowels {"aeiou"}; 
  str.find_first_of(vowels); //returns 1 
  str.find_last_of(vowels); //returns 7 

- We can invert the above 
- find_first_not_of and find_last_not_of search for the first (last) occurance 
  of any character not in the argument 
  str.find_first_not_of(vowels); //return 0 
  str.find_last_not_of(vowels); //return 10 
*/ 

 string vowels{"aeiou"}; 
 cout << "First vowel is at index " << str.find_first_of(vowels) << endl;
 cout << "Last vowel is at index " << str.find_last_of(vowels) << endl;
 cout << "First non-vowel is at index " << str.find_first_not_of(vowels) << endl;
 cout << "Last non-vowel is at index " << str.find_last_not_of(vowels) << endl;
}

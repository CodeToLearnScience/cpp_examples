/* 
-----------
erase() 
----------- 
- The erase member function removes characters from the string 
- It takes two arguments 
  * The first argument gives the index of the first element to be erased 
  * The second argument gives the number of elements to erase  
*/ 

#include <iostream> 
#include <iterator>
#include <string> 

using namespace std; 

int main(){

  string hello{"Hello"};

  hello.erase(3, 1); //erase fourth character 
  auto opos = hello.find('e'); //First occurence of 'e' 

  if(opos!=string::npos){
    hello.erase(opos, 2); //erase two elements starting with the e -> "el" 
  }

  cout << "new string after erase: " << hello << endl;

  /*---------------------
    erase() and iterators
    ---------------------
    - When used with an iterator, it will erase the corresponding element 
    */
  string str1{"hello"}; 
  auto first = begin(str1); //get iterator to first elements 
  str1.erase(first); //erase h 

  cout << "new string after erase: " << str1 << endl;

  //With an iterator range, it will erase all elements in the range 
  str1.erase(begin(str1)+1, end(str1)-1);
  cout << "new string after erase: " << str1 << endl; //erase all except first and last 

  /*---------- 
    replace()
    ---------- 
    - replace() will remove some of the characters from a string and replace 
      them with other characters 
      * The first argument is the index of the first character to be replaced  
      * The second argument is the number of characters to be replaced 
      * The remaining arguments give the characters that will replace them 
  */ 
  string str2{"Say Hello"}; 
  auto gdx = str2.find("H"); 
  if(gdx!=string::npos){
    str2.replace(gdx, 5, "Goodbye"); //replace 5 characters starting from H and replace that with Goodbye 
  }
  cout << "after replacing: " << str2 <<endl;
  /*----------------------------
    replace with iterator range 
    ----------------------------
    - The first argument is an iterator to the first character to be replaced 
    - The second argument is an iterator to one place after the last character  
      to be replaced 
    - The remaining arguments give the characters that wil replace them 
  */

  str2.replace(begin(str2), begin(str2)+3, "Wave"); 
  cout << "after replacing: " << str2 <<endl;
  
  //--------
  //assign()
  //--------
  //assign() will remove all the characters from a string and replace them with 
  //other characters 
  string str3{"Hello"};
  str3.assign("Goodbye"); 
  cout << "after assign: " << str3 << endl;
}


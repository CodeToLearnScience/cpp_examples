/*
------------------------
append() member function
------------------------ 
- The append() member function adds its argument at the back of the string 
  string hello{"Hello"}; 
  hello.append(" world"s); //String is now "Hello world" 
- Normally we use the += operator as it is easier to type and has an overload 
  which accepts a char argument 
- These come from the two different interfaces to the string class. The += is 
  from the original implementation, which made it look like a built-in type, 
  and the append member function is to make it more like a standard container
- However, we can do lot more with append. It has an overload which makes 
  adding a substring easier: 
    hello.append("wow!!!"s, 3, 2); //string is now "Hello world!!" 
    * here from string "wow!!!", it takes substring starting from 3 and adds 
      next two chars including the starting char to hello, ie., !! so the final 
      result will be "Hello world!!" 
- But append doesn't take single char for that we need to use += 

------------
insert()
------------
- More useful member function will be insert() 
- It has number of overloads 
- It adds characters before a specified position 
- We can insert a string literal or string variable 
- Its part of the container interface. So all containers will have similar 
  function 
  
    string str{"for"}; 
    str.insert(2, "lde"s}; //Insert "lde" before str[2] - "folder"

    string str2{"care"};
    string str3{"omp"};

    str2.insert(1,str3); //insert str3 before str2[1] - string is now "compare" 
*/ 

#include <iostream> 
#include <string> 

using namespace std; 


int main()
{
  string hello{"Hello"}; 
  hello.append(" world"); 

  cout << "hello = " << hello << endl; 

  string hello2("Hello"s); 

  hello2.append("wow!!!", 3, 2); 
  cout << "hello2 " << hello2 << endl; 

  //--------------
  //insert() 
  //--------------
  string str{"for"}; 
  str.insert(2, "lde"s); 
  cout << "str " << str << endl; 

  string str2{"care"}; 
  string str3{"omp"};
  str2.insert(1, str3); 
  cout << "str2 = " << str2 << endl; 

  //we can insert a substring 
  string str4{"xx"}; 
  string str5{"trombone"}; 
  str4.insert(1, str5, 4, 2); //insert "bo" before str4[1] - string now is "xbox" 
  cout << "str4 " << str4 << endl;

  //we can insert a char, multiple times 
  string str6("cash"); 
  str6.insert(1, 3, 'r'); //insert 'r' three times before str3[1] - string now is "crrrash"
  cout << "str5 " << str6 << endl;

  //we can insert at the result of a find call 
  auto opos=hello.find('o'); 
  if(opos!=string::npos){
    hello.insert(opos, 2, 'o'); //insert 'o' twice before first instance of 'o' - string now is "hellooo" 
  }
  cout << "hello " << hello << endl;

 //insert() can also take iterators 
  string str7{"word"}; 
  auto last = end(str7)-1; //get iterator to last char 
  
  //insert 'l' before last character 
  str7.insert(last, 'l'); 
  cout <<"str7: " << str7 << endl;

  string str8{"ski"}; 
  auto last2 = end(str8); //get iterator to last character + 1 
  
  //isert "l" twice, after last character 
  str8.insert(last2, 2, 'l');
  cout <<"str8: " << str8 << endl; //str is now "skill"

  /*
  -----------------------
  iterator invalidation 
  -----------------------
  - Definition: Loss of validity of an iterator, pointer, or reference to a 
    container element after a container-modifying operation. Using an 
    invalidated iterator is undefined behavior.
  - Cause: Reallocation, element relocation, erasure/insertion, or structural 
    changes that alter storage or ordering.
  - Something we need to be careful about when using iterators with insert 
    statements. The insert operation may cause any iterators that you had  
    before the operation to become invalid. For ex, the string has an internal 
    memory buffer where it stores all the data. If that memory buffer is just 
    big enough to store all the data it has, and you add some more data, then
    the buffer will no longer be big enough. In that case, the string is going 
    to allocate a new buffer and copy all the data into the new buffer and then 
    delete the old one. So if you had an iterator to the element when it was in 
    the old buffer, then that iterator will no longer be valid, because that 
    buffer is no longer part of the string. So that element is not part of the 
    string's data. 
  */

  //demonstration of iterator invalidation 
  string str9{"orld"}; 
  auto first = begin(str9); 

  //iterator to first element add 'd' 16 times at the back. This is enough to 
  //cause the string to be reallocated its memory buffer. And now all the data 
  //goes to new buffer. And you would think that just inserting some elements 
  //would not change the position of the first element. But that is now pointing 
  //to an element that is not in the buffer and you will get memory error when 
  //the program runs. The program will crash 
  str9.insert(end(str9), 16, 'd');   
  str9.insert(first, 'w'); 

  //so the thing to do here is to, "if you like", "refresh" the iterator. So 
  //we need to get the new iterator to the first element. Comment the previous 
  //line str9.insert(first, 'w');
  auto new_first=begin(str9);
  str9.insert(new_first, 'w'); 

  cout << "str9: " << str9 << endl; 
}

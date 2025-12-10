/*
In a traditional C++ 
if you have an array of chars, ints or objects of some kind

  const char str[] = {'H', 'E', 'L', 'L', 'O'};
  const char *pEnd str+5; //pointer to element after last element. points to memory not part of the array  
  const char *p = str; //pointer to start of array 

  while(p!=pEnd){ //gone past last element 
    std::cout << *p << std::endl; 
    ++p; //increment to move to next element 
  }

std::string iteration 
- When we are using a standard string, we could use the same approach, because 
  that's implemented as an array. We can get address of a first element and use 
  a pointer to that and increment it. But that's not the right way to do things 
  Although it works for strings and vector, as they are implemented as arrays, 
  bu there are other containers in the standard library which are not, and that 
  approach won't work, so the right way to do is using iterators  

*/

#include <iostream> 
#include <string>
#include <vector>

int main(){

  //the right way to do is using an iterator and it works the same way 
  //we get an iterator instead of a pointer, which represents the first element 
  //this iterator is member of the string object. Its a class itself 
  //we can use begin() and end() member functions which return iterators
  //begin() will return iterator to the first element and end() to last+1 element
  //and since it points to last+1 element its an invalid iterator and must not be dereferenced 
  //These iterators are specific to the object. They must not be mixed with iterators to the other objects 

  std::string str{"Hello"};
  std::string::iterator it=str.begin(); /*iterator to first element*/ 
  
  //Both begin and end will point to same value if there is no data in the container and loop body is not executed. 
  while(it!= str.end())/*iterator to last element plus one*/
  {
    std::cout << *it << ",";
    ++it; 
  }
  
  std::cout << "\n";
  
  //we can use iterator in for-loop as well 
  for(std::string::iterator it=str.begin(); it!=str.end(); ++it){
    std::cout << *it << ",";
  }
  
  std::cout << "\n";
  
  //we can do this with vectors as well 
  std::vector<int> vec{1,2,3,4,5}; 
  for(std::vector<int>::iterator it=vec.begin(); it!=vec.end(); ++it){
    std::cout << *it << ",";
  }
  
  std::cout << "\n";
  
  return 0;
}


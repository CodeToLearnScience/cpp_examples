/*
1. Const iterator 
- if we want to prevent the loop from modifying the string, we can use a 
  const_iterator 
  std::string::const_iterator cit; 
  for(cit = str.begin(); cit!=str.end(); ++cit){
    cout << *cit << "\n";
  }
- there are two uses 
  1. if you simply want to iterate and make sure that you don't accidentally 
    change anything. 
  2. Other one is, if you have a const container, then you need to use a const 
    iterator with it. Most common circumstance is if you're in a function body
    and you've been passed a const container. 

2. Reverse Iterator 
  - we can also use reverse iterator to iterate backwards from the last element 
    string::reverse_iterator rit; 
  - rbegin() returns a reverse iterator to the last element 
  - rend() returns a reverse iterator corresponding to "the element before the 
    first element" 

    for(string::reverse_iterator rit=str.begin(); rit!=str.rend(); ++rit)
    {
      cout << *rit << "\n"; 
    }

3. Const forms of begin() and end() 
  - Modern C++ has const versions of above and this make it easier to use auto 
    to iterate over containers 
  - cbegin() and cend() return const iterators 
  - crbegin() and crend() return const reverse iterators 

4. Non member begin() and end() 
  - C++11 provides begin() and end() global functions 
  - These are more readable than member functions 

*/


/*Some notes 

when to prefer the global std::begin/std::end and related functions, with simple rules.

Use for arrays: Built-in arrays don’t have member begin()/end(). std::begin(a)/std::end(a) return T* /T* + N for T a[N].
Generic code: In templates, prefer using std::begin; using std::end; then call begin(x)/end(x) to support both arrays and containers via ADL.
Const access: Use std::cbegin(x)/std::cend(x) to force const_iterator even if x is non-const.
Uniform interface: When you want one idiom that works across STL containers, arrays, and user-defined types that provide begin/end found by ADL.
Ranges (C++20+): Prefer std::ranges::begin(x)/std::ranges::end(x) for range-aware code; they handle more types consistently.
Non-generic, container-specific code: It’s fine to use member functions (vec.begin(), str.end()) directly—especially in straightforward, non-template code.
Practical tips:

Include <iterator> for std::begin/std::end/std::cbegin/std::cend.
In templates, add:
using std::begin; using std::end;
Then call begin(x); end(x); to let ADL find the right overload.
If you specifically need reverse iterators, use std::rbegin(x)/std::rend(x) (and std::crbegin/std::crend) or the container’s rbegin()/rend().
Rule of thumb: Prefer the free functions in generic code (and for arrays); use member functions in simple, container-specific code.

ADL 

Definition: ADL (Argument-Dependent Lookup) is a C++ rule where, when you call an unqualified function like begin(x), the compiler looks not only in the current scope and std:: (if brought in), but also in the namespaces associated with the argument types of the call.
Why it matters: It lets generic code find the “right” function for a type without you writing ns::func(...) explicitly. This is how begin(x) can work for both STL containers and user-defined types that provide begin in their own namespace.
Common use: In templates, you write using std::begin; using std::end; then call begin(x). For standard containers, ADL finds their member-based begin; for arrays, std::begin works; for custom types, their namespace begin can be found via ADL.
Example:

Suppose a type my::vec has begin(my::vec&) in namespace my.
In generic code:
using std::begin;
begin(v); // ADL finds my::begin(v) instead of requiring my::begin(v) explicitly.
In short: ADL helps the compiler discover functions in the namespaces tied to your argument types, enabling flexible, generic calls without fully qualifying function names.
*/

#include <iostream>
#include <string>
#include <vector>

int main(){
  std::string str{"Hello"}; 
  std::cout << "Iterator: "; 

  for(auto it = str.begin(); it!=str.end(); ++it){
    std::cout << *it << ", ";
  }

  std::cout << std::endl << "Reverse iterator: "; 
  for(auto rit = str.rbegin(); rit!=str.rend(); ++rit){
    std::cout << *rit << ", ";
  }

  std::cout << std::endl << "const iterator: "; 
  for(auto cit = str.cbegin(); cit!=str.cend(); ++cit){ //deduced as string::const_iterator 
    std::cout << *cit << ", ";
  }

  std::cout << std::endl << "const Reverse iterator: "; 
  for(auto crit = str.crbegin(); crit!=str.crend(); ++crit){ //deduced as string::const_reverse_iterator 
    std::cout << *crit << ", ";
  }

  //global begin() and end() functions 
  //these are more readable than the member functions 
  std::cout << std::endl << "Global  iterator: "; 
  for(auto it = begin(str); it!=end(str); ++it){ //it deduces as std::string::iterator it 
    std::cout << *it << ", ";

  }
  //begin() and end() also work with built-in arrays 
  int arr[] = {1,2,3,4,5};
  std::cout << std::endl << "Global iterator for built-in array: "; 
  for(auto it=std::begin(arr); it!=std::end(arr); ++it){ //deduced as int* it 
    std::cout << *it << ", ";
  }

  //C++14 also added cbegin(), cend(), rbegin(), rend(), crbegin(), crend() 
  std::cout << std::endl << "Global iterator cbegin for built-in array: "; 
  for(const int* cit=std::cbegin(arr); cit!=std::cend(arr); ++cit){ //deduced as const int* it 
    std::cout << *cit << ", ";
  }

  std::cout << std::endl << "Global iterator rbegin for built-in array: "; 
  for(std::reverse_iterator<int*> rit=std::rbegin(arr); rit!=std::rend(arr); ++rit){ //deduced as const int* it 
    std::cout << *rit << ", ";
  }

  std::cout << std::endl << "Global iterator crbegin for built-in array: ";
  for(std::reverse_iterator<const int*> crit=std::crbegin(arr); crit!=std::crend(arr); ++crit){ //deduced as const int* it 
    std::cout << *crit << ", ";
  }

  std::cout << "\n";
  //-----------------------------------------------------------------------------
  //Range for-loops 
  std::vector<int> vec{3,6,7,8,5};
  //special concise syntax for iterating over containers
  //only suitable only if you want to loop from start to end and visit each element once, in order without adding or removing elements 
  //actually compiler generates the code like the one shown next. Expanded version 
  for(auto el : vec){ //modifying el doesn't change vec because its a separate copy. To modify we need to use auto& el  
    std::cout << el << ", ";
  }

  std::cout << "\n";
  //the abouve one is equivalent to writing 
  for(std::vector<int>::iterator it=begin(vec); it!=end(vec); ++it){
    int el=*it;
    std::cout << el << ", ";
  }

  //to modify elements of vector we need to use reference 
  for(auto& el : vec){
    el+=2; 
  }

  //The above code is equivalent to 
  for(std::vector<int>::iterator it=begin(vec); it!=end(vec); ++it){
    int& el=*it; //el is reference to current element 
    el++;
  }
  std::cout << "\n";
  for(auto& el : vec){ 
    std::cout << el << ", ";
  }
}

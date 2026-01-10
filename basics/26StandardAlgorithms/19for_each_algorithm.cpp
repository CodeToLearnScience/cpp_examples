/*---------------
 for_each()
---------------
- for_each() calls a function on every element in an iterator range
//print each character in str on a separate line
string str{"A test string"};
for_each(cbegin(str), cend(str), [](const char c) {cout << c << ",";})

- The same code can be written more simply using a range-for loop
//range-for loop
 for(auto c: str){
  cout << c <<",";
 }

 ----------------------------
 for_each() and modification
 ----------------------------
 - The element can be passed by reference to the function
 - This allows us to change the elements
   for_each(begin(str), end(str), [](char& c){ c=toupper(c); });
- Again this can be written more simply as a range-for loop
  for(auto& c: str){
    c = toupper(c);
  }

-----------------------
for_each() vs range-for
-----------------------
- range-for loops were introduced in C++11 but algorithms came in C++98
- Before then, for_each() was a convenient way of applying a function to the
elements of a container
- Now, it is usually better to write a range-for loop
  * Clearer code than for_each()
  * Opportunity to terminate the loop with a break or return statement

  -------------------------
  Applications of for_each()
  - However, for_each() is still useful
  - can be applied to a sub-range of elements
  - Single path through code makes it easier to optimize
  - Useful stop-gap when implementations are lacking
    * Visual C++ didn't support range for loops until 2015
    * Many C++17 parallel algorithms are not implemented yet
 */

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
  // print each char in str on a separate line
  string str{"A test string"};

  cout << "With for_each: ";
  for_each(cbegin(str), cend(str), [](const char c) { cout << c << ", "; });

  // range for-loop
  cout << "\n With range for loop: ";
  for (auto c : str) {
    cout << c << ", ";
  }
  cout << "\n";
  //---------------------------------------------------------------------------
  // for_each with modification
  // convert each element in str to upper case

  for_each(begin(str), end(str), [](char &c) { c = toupper(c); });
  for (auto c : str) {
    cout << c << ", ";
  }
  cout << "\n";
}

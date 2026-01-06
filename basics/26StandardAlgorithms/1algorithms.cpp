/*
 Why use standard algorithms
 - Over 100 useful algorithms
 - shorter, clearer-avoids explicit loops
 - Highly flexible - programmer can customize functionality
 - Code reuse
    * Coded and tested as part of the standard library
    * More accurate and more efficient
    * Saves development time

------------------
Generic Algorithms
------------------
- std::string has a find() member function
- This can perform searching, but only on string objects
- The STL algorithms are global functions which will work with any kind of STL
  container
  * The container elements can also have any type
- These are known as "generic algorithms"
 */

/*
 -------------------------
 example of generic find.
 -------------------------
- accepts any container with elements of any type
- Iter=type of containers iterator, Ele=type of container elements
Iter find(Iter begin, Iter end, Elem target){
    for(Iter it=being; it!=end; ++it){ //loop over range, stopping before "end"
        if(*it==target){               //is this the value we are looking for
            return it;
        }
    }
    //we have reached the end of the loop without finding the target
    return end;
}

*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

int main() {
  string str{"Hello world"};
  cout << "String: ";

  for (auto c : str) {
    cout << c << ",";
  }
  cout << "\n";

  // search string for first occurance of '1'
  auto res = find(cbegin(str), cend(str), 'l');
  // check if we found it
  if (res != cend(str)) {
    cout << "Found a matching element at index: " << res - str.cbegin() << "\n";
  }

  cout << " At this point in the string: ";
  for (auto it = res; it != str.cend(); ++it) {
    cout << *it;
  }
  cout << "\n";
}

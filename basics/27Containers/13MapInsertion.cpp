/*
------------------
Map Insertion
------------------
- The original STL provided two ways to insert an element into a map
  * operator[]
  * The insert member function

-----------------
Operator[]
-----------------
- Operator[] provides "insert or assign" functionality
- If there already is an element in the map with the requested key, its value is
overwritten
- otherwise, a new element is inserted into the map
  map<string, int> scores; //create an std::map object
  ...
  scores["Graham"] = 66; //what effect does this have?
- There are two possible outcomes
  * We have inserted a new element with key "Graham"
  * We have overwritten the value of an existing element
- Operator[] performs an insertion in two stages
  scores["Graham"]=66;
- First it creates the new element
  * The key is the argument
  * The value is default-initialized
  * Then it assigns the value
- This requires that the value's type has a default constructor
- If the assignment throws an exception, the partially-populated element in the
map
  scores["Graham"]; //Element with key "Graham" and undefined value
- Operator [] returns a value
- This is a reference to the element's value member
   auto res = scores["Graham"] =66; //res=>66
- This does not tell us what happened

--------------
insert()
--------------
- The insert() member function will only insert a new element
- If the map already has an element with the same key, nothing happens
- The return value from insert() allows us to find out whether a new element was
added
- The value's type does not need to have a default constructor
- If an exception is thrown during the operation, the insertion has no effect

-------------------------------
Insert or Assign with insert()
-------------------------------
- auto res = scores.insert(make_pair("Graham"s, 66));
  auto iter = res.first;
  if(res.second){
    //the new element was inserted
  }
  else{
    //not inserted-we need to assign the existing element
    iter->second=66;
  }
*/

#include <iostream>
#include <map>
#include <utility>

using namespace std;

int main() {
  map<string, int> scores; // creates an empty std::map
  scores.insert(make_pair("Maybelline", 82));
  scores.insert({"Graham", 78}); // Add some elements to it

  cout << "Map elements: \n";
  for (const auto &player : scores) {
    cout << player.first << " has a score of " << player.second << "\n";
  }

  // Insert or assign an element with key "Graham" and value 66
  auto res = scores.insert(make_pair("Graham"s, 66));
  auto iter = res.first;
  if (res.second) {
    cout << "Inserted a new element with name " << iter->first;
    cout << " and score" << iter->second << "\n";
  } else {
    cout << "Modifying existing element with name " << iter->first;
    iter->second = 66;
    cout << " to have score " << iter->second << "\n";
  }
}

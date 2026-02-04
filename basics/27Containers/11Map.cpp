/*
 --------
   Map
 --------
- The C++ library provides std::map in <map>
- This is an associative container
- Each element consists of an std::pair
  * The first member is the "key" of the element
  * The second member is the "value" of the element
- Each element must have a unique key
  * The values do not have to be unique
- The elements are stored in order, using the < operator of the key to sort
the elements
- For efficiency, std::map is implemented as a tree, usually a red-black tree

--------------
Map Usage
--------------
- The "value" member of the pair is used to store the data
- The "key" is used to locate the corresponding data
  * employee ID -> personnel record
  * player's name -> performance record
- We search for a particular key, then look up the data in the value member
- The key acts like an index

-----------------------------
Adding and Removing Elements
-----------------------------
- We can use insert() and erase() as we did with std::set
- We need to pass the new element to insert() as an std::pair
  m.isert(make_pair(k,v));
- With C++11, we can use list initializer
  m.insert({k,v});
- insert() will fail if the map already has an element with the same key

-----------------
std::map insert()
-----------------
- insert() returns an std::pair, similar to std::set
- The "second" member is a bool indicating success/failure
- The "first" member is an iterator to the new element on success
  * On failure, it is an iterator to the element that caused the insert() to
fail
  * This will occur if an existing element in the map has the same key

-------------
Map Subscripting
-------------
- Unlike list and set, map supports subscripting
- However, this works differently from vector and arrays
- If the element does not already exist, it is created
  scores["Graham"];     //Fetches the value with key "Graham"
  scores["Graham"]=66;  //Changes the element with key "Graham"
  scores["Grace"]=66;   //Creates a new element with key "Grace"
- If the element does exist, this overwrites the its value

-----------------
Map Pros and Cons
-----------------
- Very fast at accessing an arbitrary element
- Insertion and deletion are usually very fast
  * Can be slow if the internal tree gets unbalanced
- Very useful for indexed data (contacts list, employee records, database query
results, etc)
- Also useful for storing data which is in the form of key-value pairs (JSON,
XML, etc)
 */

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <utility>
using namespace std;

void print(const map<string, int> &scores) {
  cout << "Map elements: \n";
  for (const auto &it : scores) {
    cout << it.first << " has a score of " << it.second << "\n";
  }
  cout << "\n";
}

int main() {

  map<string, int> scores;                    // create an empty std::map
  scores.insert(make_pair("Maybelline", 86)); // add element with make_pair
  scores.insert({"Graham", 78});              // add using list initializer

  print(scores);

  cout << "Adding element with key Graham\n";
  auto ret = scores.insert({"Graham", 66});
  if (ret.second) {
    cout << "Added element with key Graham to map\n";
  } else {
    auto it = ret.first; // iterator to existing element
    cout << "Map already contains an element with key " << it->first;
    cout << " which has value " << it->second << "\n";
  }

  print(scores);

  cout << "Removing element with key Graham\n";
  scores.erase("Graham");
  print(scores);

  auto ret2 = scores.insert({"Graham", 66});
  if (ret2.second) {
    cout << "Added element with key Graham to map\n";
  } else {
    auto it = ret2.first; // iterator to existing element
    cout << "Map already contains an element with key " << it->first;
    cout << " which has value " << it->second << "\n";
  }
  print(scores);

  cout << "Map usage with subscripting" << "\n";
  cout << "Graham has a score of " << scores["Graham"] << "\n";
  cout << "Setting Graham's score of 66\n";
  scores["Graham"] = 66;
  print(scores);

  cout << "Adding Grace's score of 66\n";
  scores["Grace"] = 66;
  print(scores);

  cout << "Calling find(\"Graham\")\n";
  auto gra = scores.find("Graham");
  if (gra != scores.end()) {
    cout << "Found an element with key: ";
    cout << gra->first << " which has a score of " << gra->second << "\n";
    // cout << "Changing Graham's name to Gra\n";
    //  gra->first = "Gra"s; //not allowed
    cout << "Changing Graham's score to 67\n";
    gra->second = 67;
  } else {
    cout << "The map has no element with the key Graham\n";
  }

  cout << "Calling find_if()\n";
  auto gra1 = find_if(begin(scores), end(scores),
                      [](pair<string, int> p) { return p.first == "Graham"s; });
  if (gra1 != scores.end()) {
    cout << "Found an element with key: ";
    cout << gra1->first << " which has a score of " << gra1->second << "\n";
    // cout << "Changing Graham's name to Gra\n";
    //  gra->first = "Gra"s; //not allowed
    cout << "Changing Graham's score to 69\n";
    gra1->second = 69;
    print(scores);
  } else {
    cout << "The map has no element with the key Graham\n";
  }

  cout << "Calling count_if()\n";
  auto n = count_if(cbegin(scores), cend(scores),
                    [](pair<string, int> p) { return p.first == "Graham"s; });

  if (n == 1) {
    cout << "The map has 1 element with key \"Graham\"\n";
  } else {
    cout << "The map has no key with the name \"Graham\"\n";
  }
}

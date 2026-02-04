/*
--------------------------
Multiset and Multimap
--------------------------
- Multiset and Multimap are very similar to set and map, except that duplicate
keys are allowed
- However, Multimap does not support subscripting

-----------------------------
insert() and erase()
-----------------------------
- insert() always succeeds for multimap and multiset
- erase(k) will remove all the elements which have the key k
  scores.erase("Graham"); //remove all elements with key "Graham"
- We can erase a single element, by passing an iterator to it
- But how do we find it?

----------------------------
The problem and solution
----------------------------
- A map can only have one matching element
- A multimap could contain many matching elements
- We need to be able to manage these multiple matches
  * Because the multimap is sorted in the order of its keys, all the matching
  elements will be next to each other
  * These form a range of elements
  * These can be represented by an iterator range
- One way to solve this problem is to use find() and count()

----------------------
Finding elements
----------------------
- c.find(k) will return an iterator to the first element with key k
  * or end() if not found
- This gives us the first element in the range
- c.count(k) will return the number of elements with key k
- This gives us the number of elements in the range
- Given these two values, we can loop over all the elements in the range
*/

#include <iostream>
#include <iterator>
#include <map>
#include <set>

using namespace std;

int main() {
  multiset<int> s; // create empty std::multiset
  s.insert(6);     // Add some elements to it
  s.insert(7);
  s.insert(4);
  s.insert(6);
  s.insert(6);

  for (auto el : s) {
    cout << el << ", ";
  }
  cout << "\n";

  cout << "===============Demonstration of Multimap=============== \n";
  multimap<string, int> scores;
  scores.insert({"Graham"s, 78});
  scores.insert({"Grace"s, 66});
  scores.insert({"Graham"s, 66});
  scores.insert({"Graham"s, 72});
  scores.insert({"Hareesh"s, 66});

  // scores.erase("Graham"); //erases all elements with the key "Graham"

  for (const auto &s : scores) {
    cout << s.first << " has a score of " << s.second << "\n";
  }

  cout << "===============Demonstration of finding same elements in "
          "Multimap=============== \n";
  auto res = scores.find("Graham");
  if (res != end(scores)) {
    auto n_matches = scores.count("Graham");

    // loop over the matching elements
    for (int i = 0; i < n_matches; ++i) {
      cout << "key = " << res->first << ", value " << res->second << "\n";
      if (res->second == 66) {
        cout << "Found an element with key Graham and value 66!\n";
      }
      ++res;
    }
  }
}

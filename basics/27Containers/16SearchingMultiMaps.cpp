/*
--------------------------
Searching Multipmaps
--------------------------
- We can find() and count() to find elements in a multiset or multimap which
have the same key
- It would be useful if we could get an iterator range for these elements
- std::multiset and std::multimap have member functions which do this
- There are also generic version in <algorithm>
  * These are useful for working with sequential containers

----------------------------
Lower and Upper Bound
----------------------------
- c.upper_bound(k) returns an iterator to the first element whose key is greater
than k
- c.lower_bound(k) returns an iterator to the first element whose key is greater
than or equal to k
  * If there is no match, it returns the same iterator as upper_bound() and the
  range is empty
- [lower_bound(k), upper_bound(k)) defines a half-open range of iterators to all
the elements with the key k
  * Equivalent to begin() and end() for the elements with key k

-------------------
Pseudo-code
-------------------
 //The key type is T
 //This must implement the < operator
 auto lower_bound(T target){
   for(auto it=begin(); it!=end(); ++it){
    if(it->first >= target){
     return it;
    }
   }
 }

 auto upper_bound(T target){
   for(auto it=begin(); it!=end(); ++it){
    if(it->first > target){
    return it;
    }
   }
 }

 ------------------
 equal_range()
 ------------------
 - equal_range() is equivalent to calling lower_bound() followed by
upper_bound()
   * It returns an std::pair
   * The first member of the pair is the return value from lower_bound()
   * The second is the return value from upper_bound()
   //iterator range for elements with key "Graham"
   auto gra_keys = scores.equal_range("Graham");
   for(auto it=gra_keys.first; it!=gra_keys.second; ++it){
   }

---------------------------------------
Finding an Element Using an Algorithm
---------------------------------------
- We can use the returned iterator range with generic algorithm
 //call find_if() with a lambda expression to search for an element with
 value 66
  auto result = find_if(start, finish, [](pair<string, int> p) {return p.second
                        == 66;});

  if(result != finish){
     cout << "Found an element with key Graham and value 66!" << endl;
  }
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void print(const pair<string, int> &score) {
  cout << "(\"" << score.first << "\", " << score.second << "), ";
}

int main() {
  multimap<string, int> scores; // create an instance of std::mutimap
  scores.insert({"Graham", 78});
  scores.insert({"Grace", 66});
  scores.insert({"Graham", 66});
  scores.insert({"Hareesh", 77});
  scores.insert({"Graham", 66});

  cout << "Multimap elements: " << "\n";
  for (auto &score : scores) {
    print(score);
  }
  cout << "\n";

  // Elements are in the order "Grace", "Graham", "Graham", "Graham", "Hareesh"
  auto gra_first =
      scores.lower_bound("Graham"); // returns an iterator to "Graham"
  auto gra_last =
      scores.upper_bound("Graham"); // returns an iterator to "Hareesh" //

  cout << "\n" << "Scores for Graham: " << "\n";
  for (auto it = gra_first; it != gra_last; ++it) {
    print(*it);
  }

  auto gord_first = scores.lower_bound("Gordon");
  auto gord_last = scores.upper_bound("Gordon");

  cout << "\n\n" << "lower_bound(\"Gordon\") returned ";
  print(*gord_first);
  cout << "\n";

  cout << "upper_bound(\"Gordon\") returned ";
  print(*gord_last);
  cout << "\n";

  cout << "=========Demonstration of equal_range()=================\n";
  auto gra_keys = scores.equal_range("Graham");
  cout << "\n" << "Results for Graham: " << "\n";
  for (auto it = gra_keys.first; it != gra_keys.second; ++it) {
    print(*it);
  }
  cout << "\n";

  // C++17
  /*
   auto [start, finish] = scores.equal_range("Graham");
   cout << "\n" << "Results for Graham: " << "\n";
   for (auto it = start; it != finish; ++it) {
    print(*it);
  }
  */

  // call find_if() with a lambda expression to search for an element with value
  // 66

  auto start = gra_keys.first;
  auto finish = gra_keys.second;
  auto result = find_if(start, finish,
                        [](pair<string, int> p) { return p.second == 66; });

  if (result != finish) {
    cout << "Found an element with key Graham and value 66!" << endl;
  }

  // since we have two Graham's with score 66. To find both
  vector<pair<string, int>> result_vec;
  while (result != finish) {
    result_vec.push_back(*result);
    ++result;
    result = find_if(result, finish,
                     [](pair<string, int> p) { return p.second == 66; });
  }

  for (auto el : result_vec) {
    print(el);
  }
  cout << "\n";

  // we can use copy_if instead of while loop to do the same
  vector<pair<string, int>> result_vec_copy;
  copy_if(start, finish, back_inserter(result_vec_copy),
          [](pair<string, int> p) { return p.second == 66; });
  for (auto el : result_vec_copy) {
    print(el);
  }
}

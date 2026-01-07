/*
 ---------
 Pair Type
 ---------
- std::pair is defined in <utility>
- It has two public data members (i don't anyother library container has public
members)
  * These can be of different types
  * They are accessed as "first" and "second"
- std::pair can be used to return two related data items from a function
- std::pair is used by some of the containers in the STL

-----------------------------
Creating a std::pair variable
-----------------------------
- std::pair is a templated type
- When we call the pair constructor, we need to specify the types of both
members
  pair<string, string> wordpair{"hello"s, "there"s};
  wordpair.first; //"hello"
  wordpair.second; //"there"
- We can call make_pair() to crate a pair variable
  auto wordpair{make_pair("hello"s, "there"s)};
- in C++17, the compiler can deduce the types
  pair wordpair{"hello"s, "there"s}; //C++17
*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// pair<string, int> find_index(const vector<string> &vec, size_t max) {
auto find_index(const vector<string> &vec, size_t max) { // we can use auto
  int idx{-1};
  auto res = find_if(cbegin(vec), cend(vec), [max, &idx](const string &str) {
    ++idx;
    return str.size() > max;
  });

  if (res != cend(vec)) {
    // return {*res, idx}; // list initialization to create a pair
    return pair{*res, idx}; // C++17 constructor which doesn't require the <>
  }
  // return {""s, idx};
  return pair{""s, idx};
}

// we can do the same with functor using C++03 or C++98
class ge_n {
private:
  const size_t n;
  int &idx;

public:
  ge_n(const size_t n, int &idx) : n(n), idx(idx) {}
  bool operator()(const string &str) const {
    ++idx;
    return str.size() > n;
  }
};

// using functor
pair<string, int> find_index1(const vector<string> &vec, int max) {
  int idx = -1;
  // write explicitly as there is no auto keyword in C++03
  // And member function vec.begin() as there is no non-member function begin()
  vector<string>::const_iterator res =
      find_if(vec.begin(), vec.end(), ge_n(max, idx));
  if (res != vec.end()) {
    return make_pair(*res, idx);
  }
  return make_pair("", idx);
}

int main() {

  pair<string, string> wordpair{"hello"s, "there"s};
  // auto wordpair {make_pair("hello"s, "there"s)};
  // pair wordpair{"hello"s, "there"s}; C++17
  cout << "First element of pair is \"" << wordpair.first << "\"" << "\n";
  cout << "Second element of pair is \"" << wordpair.second << "\"" << "\n";

  vector<string> words{"a",    "collection", "of",     "words",
                       "with", "varying",    "lengths"};

  size_t max{5};
  auto res = find_index(words, max);

  if (res.first != ""s) {
    cout << R"(The first word which is more than )" << max
         << R"( characters long is ")";
    cout << res.first << R"(")" << "\n";
    cout << "The index is " << res.second << "\n";
  }

  // without modern C++
  vector<string> words1;
  words1.push_back("a");
  words1.push_back("collection");
  words1.push_back("of");
  words1.push_back("words");
  words1.push_back("with");
  words1.push_back("varying");
  words1.push_back("lengths");

  int max1 = 5; // as there is no brace initialization with C++03
  pair<string, int> res1 = find_index1(words1, max1);

  if (res1.first != ""s) {
    cout << R"(The first word which is more than )" << max
         << R"( characters long is ")";
    cout << res1.first << R"(")" << "\n";
    cout << "The index is " << res1.second << "\n";
  }
}

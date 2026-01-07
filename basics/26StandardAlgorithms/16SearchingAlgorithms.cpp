/*
- std::string has a member function find_first_of() and works with strings
- There is a generic algorithm function, std::find_first_of() which can be used
with any container. Or infact anything which supports iterator
- This algorithm uses the equality operator == by default

--------------
adjacent_find()
--------------
- std::adjacent_find() looks for two neighboring elements that have the same
value
- It returns an iterator to the first element of the first match
- This algorithm uses the equality operator == by default

----------
search_n()
----------
- std::search_n() looks for a sequence of n successive elements which have the
same given value
- It returns an iterator to the first element of the sequence
- This algorithm uses the equality operator == by default

------------
search()
------------
- std::search() takes two iterator ranges
- It looks for an occurance of the second iterator range inside the first range
  * Similar to finding a sub-string in a string
- It returns an iterator to the first occurance
- This algorithm uses the equality operator == by default

-----------
mismatch()
-----------
- mismatch() takes two iterator ranges and looks for differences between the two
ranges
- It returns a pair to the first element that has a different value in each
range
- This algorithm uses the equality operator == by default

--------------------
"some of" algorithms
--------------------
- These three algorithms take an iterator range and a predicate
- all_of() returns true if the predicate is true for every element
- any_of() returns true if the predicate is true for at least one element
- none_of() returns true if the predicate is false for every element

---------------
binary_search()
---------------
- binary_search() is Similar to fin()
- It assumes the iterator range is sorted, which makes the search must faster
- This algorithm uses the equality operator == by default

------------
includes()
------------
- includes() takes two iterator ranges
- it also assumes the iterator ranges are sorted
- includes() returns a bool, depending on whether all the elements in the second
range are present in the first range
- This algorithm uses the equality operator == by default

*/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void print_vec(const vector<int> &vec) {
  for (auto v : vec) {
    cout << v << " ";
  }
  cout << "\n";
}

int main() {
  string str{"Hello world"};
  cout << "String to search: " << str << "\n";

  string vowels{"aeiou"};

  // returns an iterator to the first character in "vowels"
  // if it doesn't find it will return end iterator, i.e., after last element
  auto vowel =
      find_first_of(cbegin(str), cend(str), cbegin(vowels), cend(vowels));

  if (vowel != cend(str)) {
    cout << "First vowel is " << *vowel << " at index "
         << distance(cbegin(str), vowel) << "\n";
  }

  // to get the next vowel we can use the same find_first_of but use iterator to
  //  next of previously found vowel so that it starts searching after e
  auto vowel2 =
      find_first_of(next(vowel), cend(str), cbegin(vowels), cend(vowels));

  if (vowel2 != cend(str)) {
    cout << "Second vowel is " << *vowel2 << " at index "
         << distance(cbegin(str), vowel2) << "\n";
  }

  //----------------------------------------------------------------------------
  // adjacent_find
  auto pos = adjacent_find(cbegin(str), cend(str));

  if (pos != cend(str)) {
    cout << "Found ajdacent elements with value " << *pos << " at index "
         << distance(cbegin(str), pos) << "\n";
  }

  //----------------------------------------------------------------------------
  // search_n()
  vector<int> vec{1, 2, 3, 7, 7, 4, 4};
  // looks for a sequence of two elements with value 7
  // Returns an iterator to the start of the first such sequence
  auto pos1 = search_n(cbegin(vec), cend(vec), 2, 7);

  if (pos1 != cend(vec)) {
    cout << "Found two elements with value 3, starting at index"
         << distance(cbegin(vec), pos1);
  } else {
    cout << "Not found the sequence\n";
  }

  //----------------------------------------------------------------------------
  // search()
  string sub{"wo"};
  cout << "searching for sub-string : " << sub << "\n";

  // returns an iterator to the first element of "wo"
  auto pos2 = search(cbegin(str), cend(str), cbegin(sub), cend(sub));
  if (pos2 != cend(str)) {
    cout << "Found a sub-string " << sub << " starting at index "
         << distance(cbegin(str), pos2) << "\n";
  }
  //----------------------------------------------------------------------------
  // mismatch()
  vector<int> vec1{1, 2, 2, 3, 2, 3, 3};
  // the vector different at thier fourth element
  vector<int> vec2{1, 2, 2, 2, 2, 3, 3};

  cout << "vec1: ";
  print_vec(vec1);
  cout << "vec2: ";
  print_vec(vec2);

  // return a pair of iterators to the first mismatched element in each range
  // i.e., the vec2 element at index 4 has 2 but vec1 has 3. So the index of
  // those will be returned as pair
  auto mis_match = mismatch(cbegin(vec1), cend(vec1), cbegin(vec2), cend(vec2));

  // elems is a pair of iterators to the corresponding element in the two
  // vectors
  if (mis_match.first != cend(vec1) && mis_match.second != cend(vec2)) {
    cout << "found mismatch at index "
         << distance(cbegin(vec1), mis_match.first) << "\n";
    cout << "vec1 has " << *mis_match.first << ", vec2 has "
         << *mis_match.second << "\n";
  }
  //----------------------------------------------------------------------------
  vector<int> vec3{3, 1, 1, 5, 9};
  cout << "vec: ";
  print_vec(vec3);

  auto is_odd = [](int n) { return n % 2 == 1; };
  auto is_even = [](int n) { return n % 2 == 0; };

  if (all_of(cbegin(vec3), cend(vec3), is_odd)) {
    cout << "All elements of vec are odd\n";
  }
  if (all_of(cbegin(vec3), cend(vec3), is_even)) {
    cout << "All elements of vec are even\n";
  }
  if (any_of(cbegin(vec3), cend(vec3), is_odd)) {
    cout << "Some elements of vec are odd\n";
  }
  if (any_of(cbegin(vec3), cend(vec3), is_even)) {
    cout << "Some elements of vec are even\n";
  }
  if (none_of(cbegin(vec3), cend(vec3), is_odd)) {
    cout << "No elements of vec are odd\n";
  }
  if (none_of(cbegin(vec3), cend(vec3), is_even)) {
    cout << "No elements of vec are even\n";
  }
  //----------------------------------------------------------------------------
  // binary_search()
  vector<int> vec4{3, 1, 4, 1, 5, 9};
  // sort the vector
  sort(begin(vec4), end(vec4));

  cout << "sorted vector: ";
  print_vec(vec4);

  if (binary_search(cbegin(vec4), cend(vec4), 4)) {
    cout << "Vector contains 4\n";
  } else {
    cout << "Vector doen't contain 4\n";
  }

  //----------------------------------------------------------------------------
  // includes()
  // sort the strings
  sort(begin(str), end(str));
  sort(begin(vowels), end(vowels));

  cout << "String to search: " << str << "\n";
  cout << "Vowels: " << str << "\n";

  if (includes(cbegin(str), cend(str), cbegin(vowels), cend(vowels))) {
    cout << "String contains all characters from vowels\n";
  } else {
    cout << "String does not contain all characters from vowels\n";
  }
}

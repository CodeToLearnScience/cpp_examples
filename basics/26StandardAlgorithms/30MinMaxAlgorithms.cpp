/*
-------------------------
Min and Max algorithms
-------------------------
- There are a number of min and max algorithms in the C++ library
- These can take
  * Two arguments
  * Initializer list (C++11)
  * Iterator range
- They return the largest and/or smallest element
- By default, the element's < operator is used
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string word1{"first_word"};
  string word2{"word2"};

  // min() and max() with arguments
  // the return value is the largest/smallest element
  auto max_args = max(word1, word2);
  auto min_args = min(word1, word2);

  cout << "max with arguments returned \"" << max_args << "\"\n";
  cout << "min with arguments returned \"" << min_args << "\"\n";

  // min() and max() with arguments and predicate
  auto max_pred = max(word1, word2, [](const string &lhs, const string &rhs) {
    return lhs.size() < rhs.size();
  });
  auto min_pred = min(word1, word2, [](const string &lhs, const string &rhs) {
    return lhs.size() < rhs.size();
  });

  cout << "max with predicate returned \"" << max_pred << "\"\n";
  cout << "min with predicate returned \"" << min_pred << "\"\n";

  // min() and max() with an Initializer list
  auto max_int = max({"collection", "of", "words"});
  auto min_int = min({"collection", "of", "words"});

  cout << "max with Initializer list returned \"" << max_int << "\"\n";
  cout << "min with Initializer list returned \"" << min_int << "\"\n";

  // minmax() takes an arguments or an Initializer list and returns an std::pair
  // of values
  auto mm = minmax({"collection", "of", "words"});
  cout << "minmax returned an std::pair{\"" << mm.first << "\",\"" << mm.second
       << "\"}\n";

  // min_element() and max_element() takes an Iterator range and return an
  // iterator
  vector<string> words{"a",    "collection", "of",     "words",
                       "with", "varying",    "lengths"};

  auto max_words = max_element(cbegin(words), cend(words));
  cout << "max_element returned \"" << *max_words << "\"" << "\n";

  auto min_words = min_element(cbegin(words), cend(words),
                               [](const string &lhs, const string &rhs) {
                                 return lhs.size() < rhs.size();
                               });
  cout << "min_element returned \"" << *min_words << "\"" << "\n";

  // minmax_element() takes an iterator range and returns an std::pair of
  // iterators
  auto mm_el = minmax_element(cbegin(words), cend(words));
  auto m1 = mm_el.first;
  auto m2 = mm_el.second;

  cout << "minmax returned an std::pair{\"" << *m1 << "\",\"" << *m2 << "\"}\n";
}

/*
 ------------
 transform()
 ------------
 - transform() will call a given function on every element in the range
 - The result is copied into destination
 ----------------------
 in-place transform
 ----------------------
- The destination iterator is allowed to overlap the source
- This allows us to do an in-place transformation
----------------------
transform() overload
----------------------
- There is an overload of transform() which takes a second iterator range
- The function will take two arguments, and element from each range
- The result is stored in the destination

----------------------------------
case-insensitive string comparison
----------------------------------
- We can transform() to implement equal_strings()
- Make a copy of the argument strings
- use transform() to convert the copies to upper case
- call std::string operator == to compare them
 */

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

void print(const vector<int> &vec) {
  for (auto v : vec) {
    cout << v << " ";
  }
  cout << "\n";
}

bool equal_strings(const string &lhs, const string &rhs) {
  // copy the arguments
  string lhs_copy{lhs};
  string rhs_copy{rhs};

  // convert to upper case
  transform(begin(lhs_copy), end(lhs_copy), begin(lhs_copy), ::toupper);
  transform(begin(rhs_copy), end(rhs_copy), begin(rhs_copy), ::toupper);

  // compare the results
  return lhs_copy == rhs_copy;
}

void test(const string &str1, const string &str2) {
  cout << str1 << " and " << str2 << " are"
       << (equal_strings(str1, str2) ? "" : " not") << " equal\n";
}
int main() {

  vector<int> vec{3, 1, 4, 1, 5, 9};
  cout << "vector: ";
  print(vec);

  vector<int> vec2;

  // double each element in vec and use the results to populate vec2
  transform(cbegin(vec), cend(vec), back_inserter(vec2),
            [](int n) { return 2 * n; });

  cout << "vec2: ";
  print(vec2);

  //---------------------------------------------------------------------------
  cout << "===========demonstration of in-place transformation==============\n";
  cout << "the first vector after in-place transformation: ";

  transform(begin(vec), end(vec), begin(vec), [](int n) { return 2 * n; });
  print(vec);

  //---------------------------------------------------------------------------
  cout << "===========demonstration of transformation function which takes two "
          "input ranges and writes results to new vec==============\n";
  vector<int> vec3{3, 1, 4, 1, 5, 9};
  vector<int> vec4;

  // n1 is element from first iterator range vec3
  // n2 is element from second iterator range vec2
  // same thing can be implemented as vec4.push_back(vec3[i]+vec2[i])
  transform(cbegin(vec3), cend(vec3), cbegin(vec2), back_inserter(vec4),
            [](int n1, int n2) { return n1 + n2; });

  cout << "result of transform overload by adding two vectors: ";
  print(vec4);
  //---------------------------------------------------------------------------
  cout << "===========demonstration of case-insensitive string "
          "comparison==============\n";
  test("lambda", "Lambda");
  test("lambda", "Lambada");
}

/*------------------------
 Palindrome Checker
------------------------
- A palindrome is an expression which reads the same backwards
  * Madam i'm Adam
  * Able was I ere I saw Elba
  * A man, a plan, a canal - Panama!
- Special characters, punctuation and capitalization are ignored
- We will write a program which checks whether its input is a palindrome
  * If the input is not a palindrome, it will print out the mismatched
    characters and the input up to second mismatch
- We will use only STL algorithm functions (no loops)

--------------
Normalization
--------------
- First we "normalize" the string
  //Make a copy, keeping only the alphabetical characters
  copy_if(cbegin(s), cend(s), back_inserter(retval),
          [](char c){return isalpha(c);});

- //Convert all remaining characters to the same case
  transform(begin(retval), end(retval), begin(retval),
            [](char c) {return tolower(c);});


-----------
mismatch
-----------
- call std::mismatch() to compare the string to the reversed string
- We use a reverse iterator

  auto p = mismatch(cbegin(pal), cend(pal), crbegin(pal));

- The return value from mismatch() is a pair of iterators
- These point to the first mismatched element in each range
- If there is no mismatch, these will be equal to end()
  * The input string is valid palindrome!

-----------
Failure case
-----------
- If the returned are not equal to end(), the input string is not a palindrome
  * There is a mismatch between the characters at p.first and the character at
    p.second
- We make a copy of the string, up to the p.second
 //use the base() member function to convert the reverse iterator to a forward
   iterator
   copy(cbegin(pal), p.second.base(), back_inserter(outstr));
*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <iterator>
#include <string>

using namespace std;

// return a copy of the argument string
// with non-alphabetical characters removed, converted to lower case

string normalize(const string &s) {

  string retval{""};
  copy_if(cbegin(s), cend(s), back_inserter(retval),
          [](char c) { return isalpha(c); });

  transform(begin(retval), end(retval), begin(retval),
            [](char c) { return tolower(c); });

  return retval;
}

int main() {
  string s{""};
  cout << "Please enter your palindrome: ";
  getline(cin, s);

  // input string with punctuation and spaces removed
  string pal{normalize(s)};

  // call mismatch to compare the string to its reverse
  // use a reverse iterator
  auto p = mismatch(cbegin(pal), cend(pal), crbegin(pal));

  // the return value from mismatch() is a pair of iterators
  // THese point to the first mismatched element in each range
  if (p.first == cend(pal) && p.second == crend(pal)) {
    // No mismatch found - the string is the same in both directions
    cout << "\"" << s << "\" is a palindrome\n";
  } else {
    // there is a mismatch
    // The character at p.first does not match the character p.second
    cout << "\"" << s << "\"" << " is not a palindrome\n";
    // Make a copy of the string, up to the mismatchin the retval
    string outstr;
    copy(cbegin(pal), p.second.base(), back_inserter(outstr));
    cout << "'" << *(p.first) << "'" << " does not match " << "\""
         << *(p.second) << "\'";
    cout << " at \"" << outstr << "\n";
  }
}

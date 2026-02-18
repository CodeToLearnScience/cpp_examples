/*---------------------------
 Program Logic
 ----------------------------
- Generate code
- Read user input
- Normalize input
  * Alphabetical only, convert to upper case
- Find number of exact matches
- Find number of loose matches
- Display and prompt for next guess
- Until there are four exact matches

----------------------------
Finding Exact Matches
----------------------------
- Compare the colour of each peg in the user's guess and the solution
- If they are the same, write the color to a temporary object
  * Otherwise, write 0 to the temporaryobject
- Return the number of non-zero elements in the temporary object

----------------------------
Finding Loose Matches
----------------------------
- Copy the user's guess into a temporary object
- Iterate over each peg in the solution
- If a peg in the temporary object has the same colour, increment a counter
- Erase that element from the temporary object
- Return the counter
- NB this will include pegs which are in the correct place
 */

#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <iterator>
#include <random>
#include <string>

using namespace std;

namespace constants {
const int npegs = 4;
const int nturns = 10;
const int ncolours = 3;
} // namespace constants

using peg_array = std::array<char, constants::npegs>;
using color_array = std::array<const char, constants::ncolours + 1>;

namespace constants {
const color_array colours = {'R', 'G', 'B'};
}

peg_array populate() {
  peg_array code{0};
  static mt19937 mt;
  uniform_int_distribution<int> ud(0, constants::ncolours - 1);
  generate(begin(code), end(code),
           [&]() { return constants::colours[ud(mt)]; });
  return code;
}

string normalize(const string &s) {
  string retval{""};
  copy_if(cbegin(s), cend(s), back_inserter(retval),
          [](char c) { return isalpha(c); });
  transform(begin(retval), end(retval), begin(retval),
            [](char c) { return toupper(c); });
  return retval;
}

peg_array get_input() {
  string input{""}, normal{""};
  peg_array result{""};

  do {
    cout << "Enter " << constants::npegs << " characters (";
    for (auto c : constants::colours) {
      cout << c;
    }
    cout << ")" << endl;
    getline(cin, input);
    normal = normalize(input);
  } while (normal.size() != constants::npegs);
  for (int i = 0; i < normal.size(); ++i) {
    result[i] = normal[i];
  }
  return result;
}

// find the number of exact matches
// An exact match occurs when a peg in "guess" has the
// as the corresponding peg in "solution"
int exact_matches(const peg_array &guess, const peg_array &solution) {
  // create a new peg_array
  // if there is an exact match, append the color of the matches peg
  // otherwise, append 0
  peg_array matches;
  transform(
      begin(guess), end(guess), begin(solution), begin(matches),
      [](const char c1, const char c2) { return (c1 == c2) ? c1 : '\0'; });

  // return the number of exact matches (the number of non-zero elements)
  return count_if(begin(matches), end(matches),
                  [](const char c) { return c != '\0'; });
}
// find the number of loose matches
// An loose match occurs when a peg in "guess" has the same color as any peg
// in "solution"
int loose_matches(const peg_array &guess, const peg_array &solution) {

  string copy_guess;
  // counter to store the number of loose matches
  int count{0};

  // make a copy of the user's guess
  copy(cbegin(guess), cend(guess), back_inserter(copy_guess));

  // loop over the solution
  // Look for each solution peg anywhere in the user's guess
  for (auto color = begin(solution); color != end(solution); ++color) {
    auto it = find_if(begin(copy_guess), end(copy_guess),
                      [=](const char c) { return c == *color; });

    // if the solution peg is anywhere in the user's guess, increment the
    // counter. Remove the peg from the user's guess (do not process it again)
    if (it != end(copy_guess)) {
      ++count;
      copy_guess.erase(it);
    }
  }

  return count;
}

int main() {
  peg_array pegs = populate();
  // peg_array pegs = {'R', 'R', 'R', 'B'};

  bool winner{false};

  for (int i = 0; i < constants::nturns; ++i) {
    peg_array input = get_input();
    auto exact = exact_matches(input, pegs);
    auto loose = loose_matches(input, pegs) - exact;
    cout << exact << " exact match(es)" << "\n";
    cout << loose << " near match(es)" << "\n";
    if (exact == constants::npegs) {
      cout << "You have found the correct solution! ";
      for (auto peg : pegs) {
        cout << peg;
      }
      cout << "\n";
      winner = true;
      break;
    }
  }
  if (!winner) {
    cout << "Sorry! The solution was:";
    for (auto peg : pegs) {
      cout << peg;
    }
    cout << "\n";
  }
}

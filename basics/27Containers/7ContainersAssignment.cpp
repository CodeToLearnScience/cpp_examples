/*

Write a program which will

1.Reads strings entered by the user
2.Store them in a sequential container
3.Print out the strings in the order they were entered

Questions for this assignment
1. Implement this program using std::vector to store the strings. Check that
your program compiles and runs correctly.
2. Implement this program using std::list to store the strings. Check that your
program compiles and runs correctly.
3. Implement this program using std::deque to store the strings. Check that your
program compiles and runs correctly.
4. Change the list and deque versions so that they store the strings in reverse
order.
5. Do not perform any manipulation on the container elements - the strings
should already be in reverse order.
*/

#include <cstdio>
#include <deque>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
int main() {

  {
    cout << "Enter the words which will be stored and printed from vector \n";
    std::vector<string> words;
    string line;
    while (true) {
      if (!getline(std::cin, line)) {
        break; // EOF
      }
      if (line.empty()) {
        break;
      }
      std::istringstream iss(line);
      std::string word;
      while (iss >> word) {
        words.push_back(word);
      }
    }

    for (const auto &it : words) {
      cout << it << "\n";
    }
  }

  {
    cout << "Enter the words which will be stored and printed from list \n";
    std::list<string> words;
    string line;
    while (true) {
      if (!getline(std::cin, line)) {
        break; // EOF
      }
      if (line.empty()) {
        break;
      }
      std::istringstream iss(line);
      std::string word;
      while (iss >> word) {
        words.push_back(word);
      }
    }

    for (const auto &it : words) {
      cout << it << "\n";
    }
  }

  {
    cout << "Enter the words which will be stored and printed from deque \n";
    std::deque<string> words;
    string line;
    while (true) {
      if (!getline(std::cin, line)) {
        break; // EOF
      }
      if (line.empty()) {
        break;
      }
      std::istringstream iss(line);
      std::string word;
      while (iss >> word) {
        words.push_front(word);
      }
    }

    for (const auto &it : words) {
      cout << it << "\n";
    }
  }
}

#include <cstddef>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {

  string line;
  vector<pair<string, int>> words;
  map<string, std::size_t> words_map;
  while (true) {
    getline(cin, line);
    if (line.empty()) {
      break;
    }
    words.push_back(make_pair(line, line.size()));
    words_map[line] = line.size();
  }

  for (const auto &word : words) {
    cout << word.first << ", " << word.second << "\n";
  }

  cout << "Storing words in map \n";

  for (const auto &word : words_map) {
    cout << word.first << ", " << word.second << "\n";
  }
}

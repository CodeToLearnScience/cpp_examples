// reading from languages2.txt to struct and printing
// uses istringstream
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

struct language {
  std::string lang;
  std::string designer;
  int date;
};

int main() {

  std::vector<language> languages;
  std::ifstream ifile("languages2.txt");

  std::string line;

  if (!ifile) {
    std::cout << "Couldn't open the file to read\n";
    return -1;
  }

  while (std::getline(ifile, line)) {
    std::istringstream is(line);
    std::string token;
    std::string lang;
    std::string designer;
    int date;
    std::vector<std::string> temp;

    while (is >> token) {
      temp.push_back(token);
    }

    lang = temp[0];
    auto last = std::end(temp) - 1;
    date = std::stoi(*last);

    for (auto it = std::begin(temp) + 1; it < std::end(temp) - 1; ++it) {
      designer += " " + *it;
    }

    languages.push_back({lang, designer, date});
  }

  for (auto &el : languages) {
    std::cout << el.lang << " " << el.designer << " " << el.date << "\n";
  }
}

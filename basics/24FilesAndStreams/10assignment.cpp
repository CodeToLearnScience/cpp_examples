// reading from languages.txt to struct and printing
// uses istringstream
#include <fstream>
#include <iostream>
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
  std::ifstream ifile("languages.txt");
  language lang;
  std::string line;

  if (!ifile) {
    std::cout << "Couldn't open the file to read\n";
    return -1;
  }
  while (std::getline(ifile, line)) {
    std::istringstream is(line);
    language lang;
    is >> lang.lang;
    is >> lang.designer;
    is >> lang.date;
    languages.push_back(lang);

    // We can also get the following way
    /* std::string lang;
     * std::string designer;
     * int year;
     *
     * is >> lang;
     * is >> designer;
     * is >> data;
     *
     * languages.push_back({lang, designer, data}};
     */
  }

  for (auto &el : languages) {
    std::cout << el.lang << " " << el.designer << " " << el.date << "\n";
  }
}

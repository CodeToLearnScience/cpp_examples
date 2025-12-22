// strring streams are useful when interfacing to systems that expect strings
// in particular formats, GUI, os, libs
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <typename T> string To_string(const T &t) {
  ostringstream os;
  os << t;
  return os.str();
}

int main() {

  string hello{"Hello, "};
  string pi{To_string(3.14159)};
  hello += pi;
  cout << hello << "\n";

  // ostringstream example
  ostringstream ostr;
  string text;

  cout << "Please enter the a word\n";
  cin >> text; // read some data
  ostr << setw(16) << text;
  cout << "Please enter another word\n";
  cin >> text;
  ostr << setw(12) << text;
  cout << ostr.str() << "\n";

  // istringstream: useful for parsing json, xml, etc
  ifstream ifile("data.txt");

  if (!ifile) {
    cout << "Couldn't open the file!\n";
    return -1;
  }
  string line;
  vector<int> numbers;
  while (getline(ifile, line)) {
    // validation etc
    istringstream is(line);
    int num;
    while (is >> num) {
      numbers.push_back(num);
    }
  }

  double sum{0.0};
  for (auto &e : numbers) {
    cout << e << "\n";
    sum += e;
  }

  cout << "Average is " << sum / static_cast<double>(numbers.size()) << "\n";
}

#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct language {
  string lang;
  string designer;
  int date;
};

int main() {
  // Vector to store the language details
  vector<language> languages;

  // Open the file with the language data
  ifstream ifile{"languages2.txt"};

  if (ifile) {
    // Read in each line of data from the file
    string line;

    while (getline(ifile, line)) {
      string lang;
      string designer;
      int year;

      // Use an istringstream to process the line of input, one word at a time
      istringstream istring{line};
      istring >> lang;

      // The designer field can contain multiple words
      // Get the first word of the designer's name
      string temp;
      istring >> temp;
      designer = temp;

      // Get the second word of the designer's name (if there is one)
      // If not, this will be the year
      istring >> temp;

      // We use a loop to read all these words, until we encounter a number
      while (!isdigit(temp[0])) {
        designer += " " + temp;
        istring >> temp;
      }

      // We have gone past the designer field
      // Convert the year to an int
      year = stoi(temp);

      // Add this line of data to the vector
      languages.push_back({lang, designer, year});
    }

    // Print out all the languages in the vector
    for (auto language : languages)
      cout << language.lang << ", " << language.designer << ", "
           << language.date << endl;
  }
}

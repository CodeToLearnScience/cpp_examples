#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main() {
  ostream_iterator<int> oi(cout, "\n");

  for (int i = 0; i < 10; ++i) {
    *oi = i;
    ++oi;
  }

  cout << "Please enter a number: " << "\n";

  // iterator that will read int from cin
  istream_iterator<int> ii(cin);

  // read an int from the stream
  int x = *ii;
  cout << "You entered " << x << "\n";

  // to read iterator
  istream_iterator<string> iis(cin); // iterator to read strings
  istream_iterator<string> eof;      // empty iterator to compare against iis to
                                // decide when to stop reading from cintypename
  // to read in loop from iterator
  vector<string> vs;
  while (iis != eof) {
    vs.push_back(*iis);
    // vs.push_back(*iis++); //this works too
    ++iis;
  }

  for (const auto &v : vs) { // press Ctrl+D which is eof in linux
    cout << v << "\n";
  }
}

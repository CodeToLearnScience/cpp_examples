#include <iostream>
#include <sstream>

using namespace std;

int main() {
  ostringstream output; // open output stringstream
  string data{"It is time to say "};
  output << data; // write some data to the stream

  auto marker = output.tellp(); // save current file position marker
  cout << data.size() << " characters written to stream\n";
  cout << "Stream marker is " << marker << " bytes into the stream\n";

  output << "hello"; // write some more data into the stream
  cout << "Stream marker is now " << output.tellp()
       << " bytes into the stream\n";

  cout << output.str() << "\n";

  if (marker != -1) {
    output.seekp(marker); // move marker back
  }

  output << "goodnight";

  cout << output.str() << "\n";
}

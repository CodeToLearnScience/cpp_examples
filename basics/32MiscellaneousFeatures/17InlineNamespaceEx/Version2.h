
#ifndef VERSION2_H
#define VERSION2_H

#include <iostream>
#include <string>

using namespace std;
inline namespace version2 {
class Internet {
public:
  void connect() { cout << "Connected to internet\n"; };
  void login(const string &id, const string &pw) {
    cout << "Logged on with username " << id;
    cout << " and password " << pw << "\n";
  }
};

class refrigerator {
  int temperature{2};
  bool door_open{false};
  bool power_on{true};
  Internet internet;

public:
  // default constructor
  refrigerator() {
    internet.connect();
    internet.login("me", "secret");
  }

  // constructor using default login
  refrigerator(int temperature) : temperature(temperature) {
    internet.connect();
    internet.login("me", "secret");
  }

  // constructor using default temperature
  refrigerator(const string &id, const string &pw) {
    internet.connect();
    internet.login(id, pw);
  }

  // constructor with no defaults
  refrigerator(int temperature, const string &id, const string &pw)
      : temperature(temperature) {
    internet.connect();
    internet.login(id, pw);
  }

  void print() const {
    cout << "temperature = " << temperature << "\n";
    cout << boolalpha;
    cout << "door_open = " << door_open << "\n";
    cout << "power_on = " << power_on << "\n";
  }
};

} // namespace version2

#endif

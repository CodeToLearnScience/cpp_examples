/* Do not repeat yourself (DRY)
 * 1. If you are writing lot of repeated code then you probably  need to think
 * about refactoring it*/
#include <iostream>
#include <string>

using namespace std;

// use of default constructor
class refrigerator {
  int temperature;
  bool door_open;
  bool power_on;

public:
  void print() const {
    cout << "temperature = " << temperature << "\n";
    cout << boolalpha;
    cout << "door_open = " << door_open << "\n";
    cout << "power_on = " << power_on << "\n";
  }
};

// c++11: data member intialization in class
class refrigerator1 {
  int temperature{2};
  bool door_open{false};
  bool power_on{true};

public:
  void print() const {
    cout << "temperature = " << temperature << "\n";
    cout << boolalpha;
    cout << "door_open = " << door_open << "\n";
    cout << "power_on = " << power_on << "\n";
  }
};

//
class Internet {
public:
  void connect() { cout << "Connected to internet\n"; };
  void login(const string &id, const string &pw) {
    cout << "Logged on with username " << id;
    cout << " and password " << pw << "\n";
  }
};

class refrigerator2 {
  int temperature{2};
  bool door_open{false};
  bool power_on{true};
  Internet internet;

public:
  // default constructor
  refrigerator2() {
    internet.connect();
    internet.login("me", "secret");
  }

  // constructor using default login
  refrigerator2(int temperature) : temperature(temperature) {
    internet.connect();
    internet.login("me", "secret");
  }

  // constructor using default temperature
  refrigerator2(const string &id, const string &pw) {
    internet.connect();
    internet.login(id, pw);
  }

  // constructor with no defaults
  refrigerator2(int temperature, const string &id, const string &pw)
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

// since we are repeating internet.connect and internet.login, so we can use
// DRY principal
class refrigerator3 {
  int temperature{2};
  bool door_open{false};
  bool power_on{true};
  Internet internet;

public:
  void init(const string &id, const string &pw) {
    internet.connect();
    internet.login(id, pw);
  }
  // default constructor
  refrigerator3() { init("me", "secret"); }

  // constructor using default login
  refrigerator3(int temperature) : temperature(temperature) {
    init("me", "secret");
  }

  // constructor using default temperature
  refrigerator3(const string &id, const string &pw) { init(id, pw); }

  // constructor with no defaults
  refrigerator3(int temperature, const string &id, const string &pw)
      : temperature(temperature) {
    init(id, pw);
  }

  void print() const {
    cout << "temperature = " << temperature << "\n";
    cout << boolalpha;
    cout << "door_open = " << door_open << "\n";
    cout << "power_on = " << power_on << "\n";
  }
};

// delegating constructor. Calling a constructor from another constructor
// if you have lots of combinations of defaults and non-defaults, we can use
// this
class refrigerator4 {
  int temperature{2};
  bool door_open{false};
  bool power_on{true};
  Internet internet;

public:
  // default constructor
  refrigerator4() : refrigerator4(2, "me", "secret") {}

  // constructor using default login
  refrigerator4(int temperature) : refrigerator4(temperature, "me", "secret") {}

  // constructor using default temperature
  refrigerator4(const string &id, const string &pw)
      : refrigerator4(2, id, pw) {}

  // constructor with no defaults
  refrigerator4(int temperature, const string &id, const string &pw)
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

int main() {
  refrigerator fridge;
  fridge.print();

  refrigerator1 fridge1;
  fridge1.print();

  refrigerator2 fridge2;
  fridge2.print();

  refrigerator3 fridge3;
  fridge3.print();

  refrigerator4 fridge4;
  fridge4.print();
}

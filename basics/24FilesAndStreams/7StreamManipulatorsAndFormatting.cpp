#include <iomanip>
#include <ios>
#include <iostream>

using namespace std;

int main() {
  int x = 2;
  bool is_negative = x < 0;

  cout << "The value of is_negative is " << is_negative << "\n";
  cout << "is_negative is " << boolalpha << is_negative
       << "\n"; // boolapha prints 1 as true and 0 as false
  cout << " x == 2 is " << (x == 2) << "\n"; // sticky manipulator
  cout << "The numerical value of \"false\" is " << noboolalpha << false
       << "\n";

  cout << setw(15) << "Penguins " << 5
       << "\n"; // setw is only non-sticky manipulator
  cout << setw(15) << "Polar Bears " << 5 << "\n";

  cout << left << setw(15) << "Penguins " << 5 << "\n"; // left is sticky
  cout << setw(15) << "Polar Bears " << 5 << "\n";

  cout << setfill('#');
  cout << left << setw(15) << "Penguins" << 5 << "\n";
  cout << setw(15) << "Polar Bears" << 2 << "\n";
  cout << right; // set back to default
  cout << setfill(' ');

  return 0;
}

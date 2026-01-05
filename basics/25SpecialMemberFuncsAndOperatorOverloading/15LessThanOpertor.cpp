/*

 Less-than Operator Summay
 - Prototype
   * bool operator<(const T& lhs, const T& rhs);
 - How to invoke it
   * a < b;
 - Called as
   * operator < (a, b);
 - Return value
   * true when the object on the left is less than the object on the right
   * otherwise false
- Standard library and < operator
  * The Standard library uses the less-than operator for sorting and ordering
- Logical operations using the < operator
 * The < operator is sufficient to perform all comparison operations
   a==b
    !(a<b) && !(b<a)
   a>=b
    !(a<b)
   a>b
    !(a<b) && !(a==b)
   etc
- Constraints on Less-than operator
  * The result of using the < operator should be consistent with the equality
    operators
    - if a < b is true, then a==b is false and a!=b is true
    - if a == b is true, then a<b is false and b<a is false
*/

#include <algorithm>
#include <ios>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

class student {
  std::string name; // student name not necessarily unique
  int id;           // student id number - unique to each student

public:
  student(std::string name, int id) : name(name), id(id) {}
  friend bool operator==(const student &lhs, const student &rhs);
  friend bool operator!=(const student &lhs, const student &rhs);
  friend bool operator<(const student &lhs, const student &rhs);
  void print();
};

bool operator==(const student &lhs, const student &rhs) {
  if (lhs.id == rhs.id) {
    return true;
  }
  return false;
}

bool operator!=(const student &lhs, const student &rhs) {
  return !(lhs == rhs);
}

bool operator<(const student &lhs, const student &rhs) {
  return (lhs.name < rhs.name); // order by name (alphabetical sort)
}

void student::print() { cout << "Name: " << name << ", id: " << id << "\n"; }

int main() {
  student stu1("John Smith", 561234);
  student stu2("John Smith", 453811);
  student stu3("Jack Jones", 692837);

  cout << "stu1: ";
  stu1.print();
  cout << "stu2: ";
  stu2.print();
  cout << "stu3: ";
  stu3.print();

  cout << boolalpha << "\n"; // set output stream
  cout << "stu1 < stu2: " << (stu1 < stu2) << "\n";
  cout << "stu1 < stu3: " << (stu1 < stu3) << "\n\n";
  cout << "stu2 < stu3: " << (stu2 < stu3) << "\n";
  cout << "stu2 < stu1: " << (stu2 < stu1) << "\n\n";
  cout << "stu3 < stu2: " << (stu3 < stu2) << "\n";
  cout << "stu3 < stu1: " << (stu3 < stu1) << "\n\n";

  // sorting of containerss using < operator from std string
  vector<string> names = {"Dilbert", "PHB",   "Dogbert", "Asok",
                          "Ted",     "Alice", "Wally"};
  cout << "Vector before sort()\n";
  for (auto name : names) {
    cout << name << ", ";
  }
  cout << "\n";

  sort(begin(names), end(names));

  cout << "Vector after sort()\n";
  for (auto name : names) {
    cout << name << ", ";
  }
  cout << "\n";

  vector<student> students = {stu1, stu2, stu3};
  cout << "Vector before sort()\n";
  for (auto name : students) {
    name.print();
  }
  cout << "\n";

  sort(begin(students), end(students));

  cout << "Vector after sort()\n";
  for (auto name : students) {
    name.print();
  }
  cout << "\n";
}

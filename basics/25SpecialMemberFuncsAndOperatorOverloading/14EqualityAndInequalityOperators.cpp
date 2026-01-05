/*
 Equality Operator Summary
 - Prototype
   * bool operator==(const T& lhs, const T& rhs);
 - How to invoke it
   * a==b;
 - Called as
   * operator==(a,b);
 - Return value
   * true when the two objects are equal
   * otherwise false

- Similarly inequality operator
- If a class defines one of these operators, it should also define the other one
 */

#include <ios>
#include <iostream>
#include <string>

using namespace std;

class student {
  std::string name; // student name not necessarily unique
  int id;           // student id number - unique to each student

public:
  student(std::string name, int id) : name(name), id(id) {}
  friend bool operator==(const student &lhs, const student &rhs);
  friend bool operator!=(const student &lhs, const student &rhs);
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
  cout << "stu1 == stu2: " << (stu1 == stu2) << "\n";
  cout << "stu1 != stu2: " << (stu1 != stu2) << "\n\n";
  cout << "stu1 == stu3: " << (stu1 == stu3) << "\n";
  cout << "stu1 != stu3: " << (stu1 != stu3) << "\n\n";
  cout << "stu2 == stu3: " << (stu2 == stu3) << "\n";
  cout << "stu2 != stu3: " << (stu2 != stu3) << "\n";
}

/*Synthesized member functions
 * 1. Constructor
 * 2. Copy Constructor
 * 3. Assignement Operator
 * 4. New member functions  in Modern C++ for move operations
 * 5. Destructor */

#include <iostream>
#include <string>

using namespace std;

class Test {
  int i;
  string str;

public:
  // Default Synthesized member functions
  //  Test(){}
  //  Test(const Test& other) : i(other.i), str(other.str){}
  //  Test& operator=(const Test& other){
  //     i=other.i;
  //     str=other.str;
  //     return *this;
  //  }
  //  ~Test(){}

  void print() { cout << "i = " << i << ", str = " << str << "\n"; }
};

class Test1 {
  int i;
  string str;

public:
  // Default Synthesized member functions
  //  Test(){}
  //  Test(const Test& other) : i(other.i), str(other.str){}
  //  Test& operator=(const Test& other){
  //     i=other.i;
  //     str=other.str;
  //     return *this;
  //  }
  //  ~Test(){}
  // user defined constructor
  Test1(int i, const string &str) : i(i), str(str) {}
  void print() { cout << "i = " << i << ", str = " << str << "\n"; }
};

int main() {
  Test test;
  cout << "test after default constructor: ";
  test.print();
  Test test2;
  cout << "test2 after default constructor: ";
  test2.print();
  Test test3 = test;
  cout << "test3 after copy constructor: ";
  test3.print();
  test = test2;
  cout << "test after assignment operator: ";
  test.print();

  Test1 ttest(5, "Hello"s);
  cout << "test after default constructor: ";
  ttest.print();
  Test1 ttest2(7, "Goodbye"s);
  cout << "test2 after default constructor: ";
  ttest2.print();
  Test1 ttest3 = ttest;
  cout << "test3 after copy constructor: ";
  ttest3.print();
  ttest = ttest2;
  cout << "test after assignment operator: ";
  ttest.print();
}

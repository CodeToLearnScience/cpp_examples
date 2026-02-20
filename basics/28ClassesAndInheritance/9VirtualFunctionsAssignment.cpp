#include <iostream>

using namespace std;

namespace example1 {

class Base {
public:
  void print() { cout << "Base class...\n"; }
};

class Child : public Base {
public:
  void print() { cout << "Child class..\n"; }
};

class GrandChild : public Child {
public:
  void print() { cout << "GrandChild class...\n"; }
};

void print_class(Base base) { base.print(); }

void example() {

  Base base;
  print_class(base);
  Child child;
  print_class(child);
  GrandChild grand_child;
  print_class(grand_child);
}
} // namespace example1

namespace example2 {

class Base {
public:
  virtual void print() { cout << "Base class...\n"; }
};

class Child : public Base {
public:
  void print() override { cout << "Child class..\n"; }
};

class GrandChild : public Child {
public:
  void print() override { cout << "GrandChild class...\n"; }
};

void print_class(Base base) { base.print(); }

void example() {
  Base base;
  print_class(base);
  Child child;
  print_class(child);
  GrandChild grand_child;
  print_class(grand_child);
}
} // namespace example2

namespace example3 {

class Base {
public:
  virtual void print() { cout << "Base class...\n"; }
};

class Child : public Base {
public:
  void print() { cout << "Child class..\n"; }
};

class GrandChild : public Child {
public:
  void print() { cout << "GrandChild class...\n"; }
};

void print_class(Base &base) { base.print(); }

void example() {
  Base base;
  print_class(base);
  Child child;
  print_class(child);
  GrandChild grand_child;
  print_class(grand_child);
}
} // namespace example3

namespace example4 {

class Base {
  int i;

public:
  Base(int i) : i(i) {}
  virtual void print() { cout << "Base class... " << i << "\n"; }
};

class Child : public Base {
public:
  Child(int i) : Base(i) {}
  void print() { cout << "Child class..\n"; }
};

class GrandChild : public Child {
public:
  GrandChild(int i) : Child(i) {}
  void print() { cout << "GrandChild class...\n"; }
};

void print_class(Base &base) { base.print(); }

void example() {
  Base base{1};
  print_class(base);
  Child child{1};
  print_class(child);
  GrandChild grand_child{1};
  print_class(grand_child);
}
} // namespace example4

int main() {
  example2::example();
  example2::example();
  example3::example();
  example4::example();
}

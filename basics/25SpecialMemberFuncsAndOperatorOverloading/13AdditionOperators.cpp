/*
- Prototype
  T operator+(const T& lhs, const T& rhs);
- How to invoke it
  a + b;
- Called as
  operator+(a, b);
- Return value
  sum of two objects
- This is defined as a non-member function
  * for allowing conversion

+= opeator summary
- T& operator+=(const T& rhs);
- a+=b;
- a.operator+=(b)
- Returns the modified first object by reference
- This is defined as a member function

-If a class needs to define either one of these operators, it will usually need
 the other one as well
- We can implement the + operator by delegating to the += operator
 Type operator+(const Type& lhs, const Type& rhs){
    Type temp{lhs}; //make a copy of the lhs argument
    temp+=rhs; //call += operator to add the rhs argument to the copy
    return temp; //return the result
 }
*/

#include <iostream>

using namespace std;

class Complex {
  double real{0.0};
  double imag{0.0};

public:
  Complex(double r, double i) : real(r), imag(i) {}
  Complex(double r) : real(r) {}

  Complex &operator+=(const Complex &rhs) {
    real += rhs.real;
    imag += rhs.imag;
    return *this;
  }

  void print() const { cout << "(" << real << "," << imag << " )" << "\n"; }
};

Complex operator+(const Complex &lhs, const Complex &rhs) {
  Complex temp{lhs}; // make a copy of the lhs argu
  temp += rhs;       // add teh rhs to temp. Using += member function
  return temp;       // return the modified copy of the lhs argument
}

int main() {

  Complex c{1.0, 2.0};
  Complex d{2.0, 3.4};

  Complex e = c + d;
  e.print();

  c += d;
  c.print();

  // conversion
  Complex f = 1 + c; // compiler will convert 1 into complex number
  cout << "f: ";
  f.print();
}

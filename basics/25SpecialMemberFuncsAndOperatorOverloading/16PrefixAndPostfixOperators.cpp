/*
Prefix and Postfix Operators
- The prefix and postfix ++ Operators increment their argument
- The prefix version returns the incremented argument
  ++p; //equivalent to p+=1;
- The postfix version returns the unincremented argument
  p++; //equivalent to temp=p; p+=1; temp;

  ++ Operators and Arrays
  - WHen we have a pointer to an array element, the ++ Operator will move the
    pointer to the address of the next element
  - We can use this to iterate over the elements of an array
    int arr[]={4,3,2,1};
    int *p = pa; //p is a pointer to the first element of arr

    for(int i=0; i<4; i++){
        cout << *p << endl; //dereference the element at address p
        ++p;                // Move p to the address of the next element
    }

  - We coan also use this with iterators to container elements
  - with postfix Operator, we can dereference and increment in a single
    statement
    cout << *p++ << endl; //dereference the element at address p, move to next
    element
    * The increment is performed first, because the ++ Operator has higher
      precedence than the *
    * The postfix Operator moves p to the next element, then returns the orginal
      address which is then dereferenced
 - We can use either ++i or i++. It doesn't matter. Its always incremented at
   the end of the loop. But its better to use prefix version.
 - So we have two operator ++. One returns by reference and one returns by
   value. But in C++, you cannot overload on return type.
 -- So we need some way to tell the compiler, which is prefix version and which
    is the postfix and the rule is that if you put an int argument, then that is
    the postfix version. Although we put an int argument but we don't use that
----------------------------------
Overloading the Prefix ++ Operator
----------------------------------

- If we are writing a class that supports artithmetical operations, we usually
  need to implement these operators
- The prefix operator performs the increment and returns a reference to the
  incremented object
  Test& Test::operator++(){
    ++member;
    return *this;
  }

----------------------------
Overloading postfix ++ Operator
----------------------------
- The postfix operator makes a copy of the object, performs the increment and
  returns the unmodified object
- The postfix operator takes a dummy argument, to give it a different signature
  from the prefix operator

  Test Test::operator++(int t){ //t is a dummy argument
    Test temp(*thi);            //copy the current object
    ++member;                   //perform the increment operation
    return temp;                //return the orginal object
  }
-
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

  Complex &operator++();   // prefix ++ operator -- return by reference
  Complex operator++(int); // postfix ++ operator -- return by value
  Complex &operator--();   // prefix -- operator
  Complex operator--(int); // postfix -- operator

  void print() const { cout << "(" << real << "," << imag << " )" << "\n"; }
};

//+ operator non-member function
Complex operator+(const Complex &lhs, const Complex &rhs) {
  Complex temp{lhs}; // make a copy of the lhs argu
  temp += rhs;       // add teh rhs to temp. Using += member function
  return temp;       // return the modified copy of the lhs argument
}

// prefix operator: member function
Complex &Complex::operator++() {
  ++real;
  return *this;
}

// postfix operator
Complex Complex::operator++(int) {
  Complex temp(*this);
  ++real;
  return temp;
}

// prefix operator: member function
Complex &Complex::operator--() {
  --real;
  return *this;
}

// postfix operator
Complex Complex::operator--(int) {
  Complex temp(*this);
  --real;
  return temp;
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

  cout << "Initial value of c: ";
  c.print();
  cout << "Value of c after prefix ";
  c++;
  c.print();
  cout << "Value of c after postfix ";
  c.print();
}

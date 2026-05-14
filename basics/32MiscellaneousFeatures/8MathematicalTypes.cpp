/*
-----------------------
Mathematical Types
-----------------------
---------------------
std::valarray
---------------------
- std::valarray is a vector-like type based on Fortran arrays
  * Fixed size
  * Easier syntax for numerical operations
- Not widely used
  * Poorly designed
  * Compiler implementers not interested in optimizing it
  * Better to use a third-party library (Eige, Blaze, Armadillo)

---------------------------
Complex Numbers
---------------------------
- C++11 has std::complex in <complex>
- It is a templated type
- The parameter can be float, double or long double

  complex<double> q{3.0, 4.0};  //complex number. Real part 3.0, imag part 4.0
  q.real();                     //Returns 3.0
  q.imag();                     //Returns 4.0

--------------------------
Complex Numbers and I/O
--------------------------
- We can print out std::complex objects
- They are displayed in the format (real, imaginary)

  complex<double> q{3.0, 4.0};
  cout << q << endl;    //displays (3.0, 4.0)

- We can read complex numbers from input, if they are in this format

  complex<double> p;
  cout << "Enter a complex number, e.g. (1.5, 2.7)\n";
  cin >> p;

-----------------------------------
complex number operators
-----------------------------------
- std::complex supports the usual arithmetic and logical operators

  complex<double> r = p + q;
  if(p==q){
    ...
  }
  p+=1.0;    //Not ++p
            //This will be interpreted as real part 1.0 and complex part 0.0

- increment and decrement operators are nut supported. Maybe because of
ambiguity. For example in ++p, does it mean adding 1.0 to real part of imaginary
part

--------------------------------
Complex number literals
--------------------------------
- C++14 provides the literal suffix i
- This returns an std::complex object whose real part is 0.0

  auto s = 2i;       //complex number, real part 0.0, imaginary part 2.0
  auto z = 3.0+4i;   //complex number, real part 3.0, imaginary part 4.0
  p+=4i;            //increase p's imaginary part by 4.0

---------------------------
Non-member functions
---------------------------
- There are Non-member functions to covert the complex number to and from polar
coordinates

  abs(q);    //returns 5.0 (sqrt(3*3+4.4))
  arg(q);    //returns phase angle (in radians)
  conj(q);   //invert imaginary part, returns (3.0, -4.0)

- The usual exponential, power and trignometric functions are supported
  * exp, log
  * pow, sqrt
  * sin, cos, tan plus inverse and hyperbolic version
*/

#include <complex>
#include <ios>
#include <iostream>

using namespace std;
using namespace std::literals;

namespace complex_ops {
void example() {
  complex<double> p{1.0, 2.0};
  cout << "p = " << p << "\n";

  complex<double> q{3.0, 4.0};
  cout << "q = " << q << "\n";

  cout << "r = p + q\n";
  complex<double> r = p + q;
  cout << "r = " << r << "\n";

  cout << boolalpha << "p==q is " << (p == q) << endl;

  //++p; //not allowed
  p += 1;
  cout << "Incrementing p gives " << p << endl;
}

void complex_literals() {
  complex<double> p{1.0, 2.0};
  cout << "p = " << p << "\n";

  auto s = 2i;
  cout << "s = " << s << "\n";

  auto z = 3.0 + 4i;
  cout << "z = " << z << "\n";

  p += 4i;
  cout << "p = " << p << "\n";
}

void non_member_funcs() {

  complex<double> p{3.0, 4.0};
  cout << "p = " << p << "\n";
  cout << "p's magnitude is " << abs(p) << "\n";
  cout << "p's phase angle is " << arg(p) << "\n";
  cout << "p's conjugate is " << conj(p) << "\n";
  cout << "p's square is " << sqrt(p) << "\n";
  cout << "p's sine is " << sin(p) << "\n";
}

} // namespace complex_ops

int main() {
  complex<double> p;
  complex<double> q{3.0, 4.0};
  cout << q << "\n";

  cout << "Enter a complex number, e.g. (1.5, 2.7)\n";
  cin >> p;
  cout << "Number entered is " << p << "\n";
  cout << "Real part: " << p.real() << ", imaginary part: " << p.imag() << "\n";

  complex_ops::example();
  complex_ops::complex_literals();
  complex_ops::non_member_funcs();
}

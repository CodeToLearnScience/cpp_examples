/*
------------------
Bitsets
------------------
---------------
std::bitset
---------------
- C has operators for bitwise manipulation of integers. So things like bitwise
and or the left shift operator and like most of the things that C++ inherited
from C are low level and not easy to use
  * These were inherited by C++
- C++11 provides std::bitset in <bitset>
- Abstraction which represents group of bits
- std::bitset is a templated type
- The parameter is the number of bits

  bitset<8> b1{"10101110"};   //initialize from string
  bitset<8> b2{0xae};         //initialize from integers including hex literal
  bitset<8> b3{0b1010'1110};  //initialize from binary constant(literal) (C++14)

----------------------
Data Access
----------------------
- Bitsets can be used with streams
  cout << b1 << "\n"; //Displays 10101110
- We can access that data in bitset by calling a member function
  * to_ulong() returns it as an unsigned long
  * to_ullong() returns it as an unsigned long long
  * to_string() returns it as a string
- The size() member function gives the number of bits in the bitset
- We can use subscript notation to access individual bits
- index 0 represents the Least Significant Bit

  bitset<8> b1{"10101110"};
  std::cout << b1[0] << "\n"; //displays 0

- test() accesses a bit with bounds checking for extra safety

  b1.test(8); //throws std::out_of_range

-------------------------
Bit Operators
-------------------------
- Member functions which operate on bitsets. This can modify all bits or one bit
- set()
  b.set()            //set all bits to true
  b.set(0);          //set bit 0 to true
  b.set(0, false);   //set bit 0 to false

- reset()
  b.reset();        //set all bits to false
  b.reset(7);       //set bit 7 to false

- flip()
  b.flip();       //invert all bits
  b.flip(7);      //invert bit 7

-----------------------
Bitset Checks
-----------------------
- all() returns true if all bits are set
  b1.all();
- any() returns true if at least one bit is set
  b1.any();
- none() returns true if no bits are set
  b1.none();
- count() returns the number of set bits
  b1.count()
*/

#include <bitset>
#include <cstddef>
#include <ios>
#include <iostream>

using namespace std;

namespace bitset_ops {

void example() {

  bitset<8> b1{
      "10101110"}; // initialize from string literal - bitset with value 174

  bitset<8> b2{0b010'1110}; // initialize from binary constant (C++14)
  cout << "b1 is " << b1 << "\n";
  cout << "~b1 is " << ~b1 << "\n";
  cout << "b2 is " << b2 << "\n";
  cout << "b1 & b2 is " << (b1 & b2)
       << "\n"; // need bracket because of operator precedence rules
  cout << "b1 | b2 is " << (b1 | b2) << "\n";
  cout << "b1 ^ b2 is " << (b1 ^ b2) << "\n";
  cout << "b1 << 4 is " << (b1 << 4) << "\n";
  cout << "b2 >> 2 is " << (b2 >> 2) << "\n";
}

void mem_functions() {
  bitset<8> b1{"10101110"}; // bitset with value 174

  cout << "b1 = " << b1 << "\n";
  auto b2 = b1;
  cout << "Calling b2.set()\n";
  b2.set(); // set all bits to true
  cout << "b2 = " << b2 << "\n";
  auto b3 = b1;
  cout << "Calling b3.set(0)\n";
  b3.set(0); // set bit 0 to true
  cout << "b3 = " << b3 << "\n";
  cout << "Calling b3.set(0, false)\n";
  b3.set(0, false);
  cout << "b3 = " << b3 << "\n";
  auto b4 = b1;
  cout << "Calling b4.reset()\n";
  b4.reset();
  cout << "b4 = " << b4 << "\n";
  auto b5 = b1;
  cout << "Calling b5.reset(7)\n";
  b5.reset(7);
  cout << "b5 = " << b5 << "\n";
  auto b6 = b1;
  cout << "Calling b6.flip()\n";
  b6.flip();
  cout << "b6 = " << b6 << "\n";
  auto b7 = b1;
  cout << "Calling b7.flip(7)\n";
  b7.flip(7);
  cout << "b7 = " << b7 << "\n";
}

void bit_checks() {

  bitset<8> b1{"10101110"}; // bitset with value 174

  cout << "b1 = " << b1 << "\n";
  bitset<8> b2;
  b2.set();
  cout << "b2 = " << b2 << "\n";
  bitset<8> b3;
  b3.reset();
  cout << "b3 = " << b3 << "\n\n";
  cout << boolalpha << "Are all bits set?\n";
  cout << "b1: " << b1.all() << "\n";
  cout << "b2: " << b2.all() << "\n";
  cout << "b3: " << b3.all() << "\n\n";

  cout << boolalpha << "Are any bits set?\n";
  cout << "b1: " << b1.any() << "\n";
  cout << "b2: " << b2.any() << "\n";
  cout << "b3: " << b3.any() << "\n\n";

  cout << boolalpha << "Are no bits set?\n";
  cout << "b1: " << b1.none() << "\n";
  cout << "b2: " << b2.none() << "\n";
  cout << "b3: " << b3.none() << "\n\n";

  cout << "Number of bits set?\n";
  cout << "b1: " << b1.count() << "\n";
  cout << "b2: " << b2.count() << "\n";
  cout << "b3: " << b3.count() << "\n\n";
}
} // namespace bitset_ops

int main() {

  bitset<8> b1{
      "10101110"};    // initialize from string literal - bitset with value 174
  bitset<8> b2{0xae}; // initialize from integer (decimal or hexadecimal)
  bitset<8> b3{0b1010'1110}; // initialize from binary constant (C++14)

  cout << "b1 is " << b1 << "\n";                         // displays 10101110
  cout << "b2 in decimal is " << b2.to_ulong() << "\n";   // displays 174
  cout << "b2 as a string is " << b2.to_string() << "\n"; // displays 10101110
  cout << "b3 is " << b3 << "\n";                         // displays 10101110

  cout << "b1 has " << b1.size() << " bits\n"; // displays 8

  // displays all the bits in b1
  cout << "The bits of b1 are: ";
  for (std::size_t i = 0; i < b1.size(); ++i) {
    std::cout << b1[i] << ",";
  }
  cout << "\n";

  // bitwise access with bounds checking
  cout << "Trying access to bit 8 of b1 with bounds checking\n";
  try {
    std::cout << "b1 bit " << 8 << " = " << b1.test(8) << "\n";
  } catch (std::exception &e) {
    cout << "Caught exception: " << e.what() << "\n";
  }

  cout << "\n---------bitwise ops------------\n";
  bitset_ops::example();
  cout << "\n---------bitset functions------------\n";
  bitset_ops::mem_functions();
  cout << "\n---------bitset checks------------\n";
  bitset_ops::bit_checks();
}

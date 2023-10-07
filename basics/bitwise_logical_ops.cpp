#include <stdio.h>
#include <iostream>

/**
* The & (bitwise AND) in C or C++ takes two numbers as operands and does AND on every bit of two numbers. The result of AND is 1 only if both bits are 1.
*
* The | (bitwise OR) in C or C++ takes two numbers as operands and does OR on every bit of two numbers. The result of OR is 1 if any of the two bits is 1.
* 
* The ^ (bitwise XOR) in C or C++ takes two numbers as operands and does XOR on every bit of two numbers. The result of XOR is 1 if the two bits are different.
*
* The << (left shift) in C or C++ takes two numbers, left shifts the bits of the first operand, the second operand decides the number of places to shift.
*
* The >> (right shift) in C or C++ takes two numbers, right shifts the bits of the first operand, the second operand decides the number of places to shift.
*
* The ~ (bitwise NOT) in C or C++ takes one number and inverts all bits of it 
*/

int main(){

  //a = 5(00000101), b = 9(00001001)
  unsigned char a = 5, b = 9;

  //The result is 00000001
  int bitwise_and = a & b;
  
  //The result is 00001101
  int bitwise_or = a | b;
  
  //The result is 00001100
  //we can use auto also
  auto bitwise_xor = a ^ b;

  //The result is 11111010
  auto bitwise_not = ~a;

  //The result is 00010010
  auto bitwise_left_shift = b << 1;

  //The result is 00000100
  auto bitwise_right_shift = b >> 1;


  std::cout << "bitwise and (a & b): " << bitwise_and << "\n" 
            << "bitwise or (a | b): " << bitwise_or << "\n"
            << "bitwise xor (a ^ b): " << bitwise_xor << "\n"
            << "bitwise not of a (~a): " << bitwise_not << "\n"
            << "bitwise left shift of b ( b << 1): " << bitwise_left_shift << "\n"
            << "bitwise right shift of b (b >> 1): " << bitwise_right_shift << "\n";
  return 0;
}

//size of the c++ types depends on the implmentation 
//char 8 bits 
//int: At least 16bits 
//long: at least 32 bits. Must have at least as many as int 
/*long long 
  - New in C++ 
  - At least 64bits. Must have at least as many as long 

  Fixed width integers 
  - Introduces in C++ 11 in <cstdint> 
  - int8_t, int16_t, int32_t, int64_t
  - Unsigned versions: uint8_t, uint16_t, uint32_t, uint64_t 

  -We can have different bases for ints 
  -Numerical literals are decimal by default int decimal=42; 4*10+2*1
  -Hexaedcimal numbers have 0x or 0X in front int hexaedcimal=0x2a; 2*16+10*1=42
  -Octal numbers have 0 in front: int octal=052; 5*8+2*1=42  Note: careful when
    you are converting string to int which have 0 at the beginning '0godmy'
  -Binary numbers have 0b or OB in front (C++ onwards): int binary=0b101010; 1*32+1*8+1*2=42 
*/

#include <iostream> 

using namespace std; 

int main(){

  //decimal 
  int decimal=42; 
  cout << "Decimal: " << decimal <<"\n";
 
  //hexaedcimal numbers have 0x or 0X 
  int hexaedcimal = 0x2a;
  cout << "Hexaedcimal: " << hexaedcimal <<"\n";

  //octal numbers start with 0 
  int octal=052; 
  cout << "Octal: " << octal <<"\n";
  
  //binary numnbers start with 0b or 0B 
  int binary=0b101010; 
  cout << "Binary: " << binary <<"\n";

  return 0;
}

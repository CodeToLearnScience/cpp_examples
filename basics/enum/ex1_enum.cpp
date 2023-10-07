#include <iostream>
#include <cstdint>

enum itr{
  car,
  bike,
  bus,
  cycle
};

enum class color: int {
  red=0,
  blue=1,
  yellow=2,
  green=3,
  orange=4,
};
  
// altitude may be altitude::high or altitude::low
enum class altitude: char{ 
     high='h',
     low='l', // C++11 allows the extra comma
}; 

//to print enum values of altitude
std::ostream& operator<<(std::ostream& os, altitude al)
{
    return os << static_cast<char>(al);
}

//to print enum values of color
std::ostream& operator<<(std::ostream& os, color c)
{
    return os << static_cast<int>(c);
}

int main(){

  ///simple enum example
  std::cout << bus << std::endl;

  ///enum class example
  color c;
  c = color::green;
  std::cout << c << std::endl;
 
  //enum altitude
  altitude a;
  a = altitude::low;
  std::cout << a << std::endl;
 
  //directly printing enum values
  std::cout << static_cast<int>(color::yellow) << std::endl;   
 
  return 0;
}



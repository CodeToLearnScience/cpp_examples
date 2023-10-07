#include <iostream>
#include <map>


int main(){

  ///declaring map
  std::map<int, int> dum{{1, 2}};
  
  ///printing value by specifying key
  ///useful while passing to function
  std::cout << dum.at(1) <<"\n";


  return 0;
}

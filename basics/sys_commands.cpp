#include <iostream>
#include <stdlib.h>


int main()
{

  system("free -h | awk 'FNR==2{print$2}'");
  
  return 0;

}

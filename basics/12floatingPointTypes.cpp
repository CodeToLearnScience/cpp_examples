#include <iostream> 


int main(){
  //float: usually 6 digits precision 

  //double: usually 15 digits precision 

  //long double: usually 20 digits precision 

  //we can use 'in numeric literals to separate digits C++14 
  const int one_million=1'000'000;
  double pi=3.141'593; 
    
  //This can go anywhere inside the number but not at the start or end 
  const int one_lakh=1'00'000; 
  
  //floating-point literals are double by default 
  3.14159; 

  //integer literals are int by default 
    //if they are too big for int, they are long 
    //if too big for long, they are long long 

  //we can add a suffix to change the type of literal 
  3.14159f; 
  1234567890ULL; 

  return 0; 
}

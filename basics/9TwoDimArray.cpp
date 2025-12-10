/*
In memory, two dimensional array is stored as a single memory block. So looks 
like 1D array 
*/

#include <stdio.h> 
#include <string>
#include <iostream> 

int main(){
  //since 2D array is single memory block we can initiaze as 1D array 
  std::string names[2][4]={"Bangalore", "Mysore", "Tumkur", "Chitradurga", 
    "Belagavi", "Davanagere", "Shivamogga", "Mangalore"};

  //For clarity we initiaze it as two nested arrays 
  std::string names1[2][4]={{"Bangalore", "Mysore", "Tumkur", "Chitradurga"}, 
    "Belagavi", "Davanagere", "Shivamogga", "Mangalore"};

  //*names[0] will give pointer entire row. To get first element  
  std::cout << *names[0] <<"\n";
  //to get second element 
  std::cout << *(names[0]+1) <<"\n";

  //similarly *names[1] will give pointer to second row 
  std::cout << *names[1] << "\n";
  //to get second element of second row 
  std::cout << *(names[1]+1) << "\n";

  //you can get first element of second row directly as follows becuase data 
  //is arraned in single memory block 
  std::cout << *(*names+4) << "\n";
  //or 
  std::cout << *(names[0]+4) << "\n";

  //flatten two-dimensional array in to one-dimensional array. Useful for performance
  //The reason for performance is, in 2D arrays, when we access inner array, we 
  //need to derefernce pointers as shown above which is constlier compared to 
  //multiplication when we use flat arrray. On modern harware multiplication is 
  //much faster than pointer derefernce 
  std::string names_flat[] = {"Bangalore", "Mysore", "Tumkur", "Chitradurga", 
    "Belagavi", "Davanagere", "Shivamogga", "Mangalore"};

  //then we can compute offsets to access different elements 
  std::cout << "-----------flat array-----------"<<"\n";
  for(int row=0; row<2; ++row){
    for(int col=0; col<4; ++col){
      std::cout << names_flat[row*4+col] << ",";
    }
    std::cout << "\n";
  }

  return 0;
}

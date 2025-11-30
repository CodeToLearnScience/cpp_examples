#include <stdio.h> 
#include <iostream> 

//pass by value
int func1(int y1){
  std::cout << "Address of y1: " << &y1 << "\n";
  return y1;
}

//pass by address 
void func2(int *y2){
  std::cout << "Address of y2: " << y2 << "\n";
  *y2=2;
}

//pass by reference 
void func3(int &y3){
  std::cout << "Address of y3: " << &y3 << "\n";
  y3=3;
}

int main(){

  int x1=1;
  std::cout << "Address of x1: " << &x1 << "\n";
  
  //value of x1 is copied to y1 so there is a extra int created in mem 
  //This is copied to z1, so there is a extra int created in mem for z1
  int z1=func1(x1);
  std::cout << "Address of z1: " << &z1 << "\n";
  
  //x1 is passed by address so no copy
  func2(&x1);
  std::cout << "Value of x1 after changing in func2: " << x1 << "\n";

  //x1 us passed by reference so no copy: Actually its func2 implemented with 
  //pointers inside. Just a easier syntax with reference. 
  func3(x1);
  std::cout << "Value of x1 after changing in func3: " << x1 << "\n";
 
  return 0; 
}

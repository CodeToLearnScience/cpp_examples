#include <stdio.h> 
#include <iostream> 

void func(int i){
  std::cout << "func(int) called " << "\n";
}

void func(int *i){
  std::cout << "func(int*) called " << "\n";
}

int main(){
  func(NULL);   //func(int) will be called as NULL is implemented as integer 
  func(nullptr); //func(int*) will be called as it can be converted to any pointer type 
  return 0;
}

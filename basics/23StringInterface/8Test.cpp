#include <cctype>
#include <iostream>
#include <string> 


using namespace std; 

//to replace all the punctuation with ! 
string exclaim(string& str){  
  for(auto &c:str){
    if(ispunct(c)){
      c='!';
      //str.replace(c, c+1, '!');
    }
  }
  return str; 
}

int main(){
  string str{"To be, or not to be, that is the question:"}; 
  cout << exclaim(str) << endl; 
}

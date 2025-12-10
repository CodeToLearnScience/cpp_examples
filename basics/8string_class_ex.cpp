#include <stdio.h> 
#include <iostream>

class URL{

public:
  URL(const std::string& protocol, const std::string& resources) : protocol(protocol), resources(resources){}

  void display(){
    std::cout << protocol << "://" << resources << "\n";
  }
private:
  std::string protocol; 
  std::string resources; 
};

int main(){

  URL url("https", "www.google.com");
  url.display();
  return 0;
}

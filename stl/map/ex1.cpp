#include <iostream>
#include <map>
#include <vector>

int main(){
  
  ///creating map
  std::map<std::string, std::vector<double>>  bc; 

  ///one way of assingning values to map container
  for (std::size_t i=0; i<10; i++){
    bc["inlet"].push_back(0.1*i);
  }


  for(std::size_t i=0; i<5; i++){
    bc["far-field"].push_back(0.2*i);
  }
   
  for(std::size_t i=0; i<5; i++){
    bc["inlet"].push_back(0.3*i);
  }

  ///assigning array index notation
  bc["outlet"]={0.1,0.2,0.3};

  ///assignment using member function insert() and STP pair
  bc.insert(std::pair<std::string, std::vector<double>>("wall", {1.2,3,3,4.5}));

  ///assignment using member function insert and value_type
  bc.insert(std::map<std::string, std::vector<double>>::value_type("symmetry", {1.2,3,3,4.5}));
 
  ///assignment using member function insert() and make_pair()
  std::vector<double> temp;
  temp.push_back(9.0);
  temp.push_back(8.0);
  temp.push_back(7.0);

  bc.insert(std::make_pair("pressure_outlet", temp));
  
  ///printing map
  std::cout << "------------------------------------------" << "\n";
  std::cout << "-------printing using std iterators-------" << "\n";
  std::cout << "------------------------------------------" << "\n";
  ///printing pre-c++17
  std::map<std::string, std::vector<double>>::iterator it;
  for(it=bc.begin(); it!=bc.end(); it++)
  {
    std::vector<double> it_vec = it->second;
    
    for(std::size_t i=0; i < it_vec.size(); i++){
        std::cout << "key: " << it->first 
                  << "\t" << "val: " << i << "\n";
    }
  }

  std::cout << "--------------------------------------" << "\n";
  std::cout << "---------printing using auto----------" << "\n";
  std::cout << "--------------------------------------" << "\n";
  ////printing using auto
  for(auto &it : bc){
    for(auto &it1 : it.second){
        std::cout <<"key: " << it.first << "\t" << "value: " << it1 << "\n";
    }
  }

  std::cout << "-----------------------------------------------------------" << "\n";
  std::cout << "-----printing using [key, value] feature of c++17----------" << "\n";
  std::cout << "-----------------------------------------------------------" << "\n";
  ///printing map using c++17 feature
  ///[key,value]: c++17 feature
  for(auto &[key, value] : bc){
    for (auto &val: value){
      std::cout << "key: " << key << "\t" << "value: " << val <<"\n";
    }
  }

  return 0;
}

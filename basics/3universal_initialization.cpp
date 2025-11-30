

int x{1}; //equivalent to int x=1
string s{"hello c++"}; //equivalent to string s("hellp c++")

std::vector<int> vec{1,2,3,4,5};

//with uniform initialization, narrowing conversions are not allowed 
int x=7.7; //old, allowed by compiler, althogh it may warn 
int x{7.7}; //not allowed 

//consistent 
vector<int> old_one(4); //vector with element 0,0,0,0
vector<int> old_two(4,2); //vector with element 2,2,2,2
vector<int> uni{4}; //vector with one element {4}
vector<int> uni{4,2}; //vector with two elements {4,2}

//avoids ambiguity
Test test(); //oject creation or function declaration 
Test test{}; //object creation a


//Declaration
std::vector<std::vector<int>> vec_of_vec; //earlier you had to have space std::vector<std::vector<int> > //space after <int> in C++03

//Aliases 
typedef vector<int> IntVec; //old C++ 
using IntVec = vector<int>; //Modern C++  

vector<IntVec> vec_of_vec; 

//nullptr
//Earlier both C and C++ defined NULL as 0 but didn't define what type. Some used int some pointer to int 
//In modern C++ we have nullptr literal which can be converted to any other kidn of ptr, but can't be converted to an integer. 
void func(int);
void func(int *);

int main(){
  func(nullptr); //calls func(int *) as expected 
}


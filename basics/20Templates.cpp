#include <iostream>
#include <vector>
using namespace std;
/* 
  - C++ templates allow us to write code that works with any type of data. This 
    is known as "generic programming". We don't mean templates are generic 
    programming, but it is a example of generic programming where you can use 
    any type 
-------------------------------------------------------------------------------
Template instantiation
-------------------------------------------------------------------------------
- When we use template with data of particular type, the compiler will generate 
  the code needed for that type 
  * vector<int> will cause the compiler to define a class that is vector of 
    ints 
  * The compiler will insert source code for the class definition into the 
    translation unit. Translation unit is basically source code file, as it is 
    seen by the compiler. That's .cc or .ccp file with all headers included and 
    preprocessed 
  * This code will then be compiled as part of the program 
- This is called an "instantiation" of the template. That is the process in 
  which the compiler generates the code for vector of int 
- This is all done automatically when compiler sees vector<int> 
- For this to be possible, the compiler must see the full definition of the 
  vector template class in the translation unit. And normally that means 
  putting it in one of the headers 

-------------------------------------------------------------------------------
Writing a Template 
-------------------------------------------------------------------------------
- When we write a template, we use a "dummy" type to show the compiler what the 
  code looks like 
- This dummy type is called "the template parameter" 
- A template can be either a function template or a class template 
*/

//Function template for finding maximum of two values 
template <class T> //T is the template parameter 
T Max(const T& t1, const T& t2){
  if(t1>t2)
      return t1; 
  return t2; 
}

/*
-------------------------------------------------------------------------------
Using a Template
-------------------------------------------------------------------------------
- When we call Max(), the compiler will instantiate the function from the 
  template code, with T replaced by the type of the arguments 
    cout << Max(7.1, 9.6) << endl; 
- The compiler deduces that the argument type needs to be double 
- The compiler will generate a definition of Max function, in which T is 
  replaced by double 

  double Max(const double& t1, const double& t2){ //replace T with double 
    if(t1>t2)
      return t1; 
    return t2; 
  }
- add this code to translation unit 
*/ 

/*
-------------------------------------------------------------------------------
Templates and code organization
-------------------------------------------------------------------------------
- With a regular function, the compiler only needs to be able to see its 
  declaration when it is called like number and  types of its arguments 
    * compiler has to check that the types are use correctly in the call 
- For a template function, the compiler must be able to see the full definition 
  when it is called 
    * The compiler has to generate the instantiated code for that call 
- Easiest way to do it is to write in header, so it is included automatically
  * this is what most programmers do 
- Some programmers put all their templates in a separate ".inc" file and 
  include that file separately 
*/

/*
-------------------------------------------------------------------------------
Class Templates 
-------------------------------------------------------------------------------
- We can write classes that work with data of any type 
  
  template <class T>
  class Test{
    T data; 
    Test(const T& data) : data(data) {}
  }

-To create an instance of this class, we put the type in angle brackets (optional 
  for function but compulsory for class) 
  
  Test<string> test{"Hello"};
  
  //Then compiler goes that template and instantiates and generates the following 
  // class with unique name. parameter T will be replaced by string  
  class Test_xcafafd{ //instantiated with unique name 
    string data; 
    Test(const string&data) : data(data) {}
  }

-------------------------------------------------------------------------------
Constructor argument deduction in C++17 
-------------------------------------------------------------------------------
- When we create an object of a templated class, the C++17 compiler can deduce 
  the parameter type 
  vector<int> vec{1,2,3}; //C++11-declared as vector<int> 
  vector vec{1,2,3}; //C++17-deduced as vector<int> 
- And this deduction mechanism is called CTAD (Constructor Template Argument Deduction) 
- So it means we can call constructor same way we call a template function. We 
  don't need to give the type of the parameter 
- It only works if the declaration has an initializer in it, otherwise the 
  compiler can't work out what the type is 
- CTAD make many declarations simpler  
 
-------------------------------------------------------------------------------
typename 
-------------------------------------------------------------------------------
- Originally, the class keyword had had to be used for a template parameter 
  template<class T> 
  ...

- The "typename" keyword" was added in C++98 
  template<typename T>
  ...

- The "class" keyword was felt to be confusing as templates can be instantiated 
  for built-in types as well as classes 
- However, many programmers still continue to use it 
*/
int main(){
  cout << Max(7.1, 9.6) << endl; 
  cout << Max<double>(7.1, 9.6) << endl; //if we want we can put <double>, that will force compiler to instantiate with double 

  //CTAD: no type needs to be specified like vector<double> 
  vector vec{1.2,3.4,5.0}; 
  for(auto el : vec){
    cout << el << ", ";
  }
  cout << endl;
}

/* 
Namespce 
- Its another tool that helps us organize code 
- We can use Namespces for grouping together logically related symbole 
  * typically done with libraries 
- The C++ standard library defines the std namespace 
  * This groups together the names of all the functions, types and variables 
    defined by it 

Why Namespces? 
- large programs often include several libraries 
  * this can lead to name conflicts 
  * e.g. two libraries could define a Test class 
- One soultion is to add library-specific prefix to the same 
  * class abc_Test 
  * class xyz_Test;
- Putting these prefixes is tedious and error-prone 
- So c++ addresses this by using namespaces 
------------------
Namespace example 
------------------ 
- we create a namespace using the namespace keyword, followed by the name we 
  wish to use for the namespace 
  //namespace for abc company 
  namespace abd{...}
  * we put the symbols we want to declare in this namespace inside the braces 
  * every symbol declared inside the namespace will have the namespace's name 
    automatically prefixed to it by the compiler 
    namespace abd{
      class Test; //This defines the symbol abd::Test 
    }
- If we want to use the symbol outside the namespace, we put abc:: in front of 
  it 
  abd::Test alphaTest; 

-------------------------------------------------------------------------------
Global namespace 
-------------------------------------------------------------------------------
- if a name is not in any namespace, it is said to be in a "global namespace" 
  * if we define a symbol which is not any namespace, the compiler will assume 
    it is in the global namespace 
- global namespace has no name 
- if we want to specify that we are referring to the global namespace, we use 
  :: on its own before the name 
  clas Test{...} //Another definition of class Test (not in the namespace) 
  ::Test test //create an object of the global class Test 

-------------------------------------------------------------------------------
Namespace splitting 
-------------------------------------------------------------------------------
- Namespaces can be split over different parts of the code, and even over 
  different files. 
  namespace and{
    class Test{...} //definition of calss Test in header   
  }

  namespace abd{
    int Test::do_test(int value) const{...} //member function definition in .cc file  
  }

-------------------------------------------------------------------------------
Name hiding 
-------------------------------------------------------------------------------
- When a symbol is defined in a namespace, it "hides" any symbols outside the 
  namespace with the same name 

  int x=23; //x defined in the global namespace 

  namespace abc{
    int x=47; //x defined in the namespace abd- hides global x 
    void func(){
      cout << "x= " << x << endl; //will use abc's x=>47 
      cout << "x= " << ::x << endl; //will use global x=>23 
    }
  }


-------------------------------------------------------------------------------
Using declarations 
-------------------------------------------------------------------------------
- A "using" declaration will bring a particular version of a class Test into 
  the global namespace 
    
    using xyz::Test; //"Test" will refer to xyz's class 
- The above will make xyz::Test available as "Test"
  * Test //xyz's class. Like an alias to xyz::Test  
  * abc::Test //abc's class 
  * ::Test //global class test 
- Once we write using declaration, this will take effect until the end of the 
  enclosing scope. Or if you do it at the global scope, then it is going to be 
  in effect until the end of the file. 


-------------------------------------------------------------------------------
using Directive 
-------------------------------------------------------------------------------
- A "using" directive will bring everything from a namespace into the global 
  namespace 
- Not good practice as it contradicts the point of having namespaces 

  using namespace std; //bring in all names from std namespace 
*/

#include <iostream> 

using namespace std; 

int x{23}; 

namespace abc{
int x{47}; //x defined in the namespace abd- hides global x 
void func(){
  cout << "x= " << x << endl; //will use abc's x=>47 
  cout << "::x= " << ::x << endl; //will use global x=>23 
}
}

int main(){
  abc::func();
}


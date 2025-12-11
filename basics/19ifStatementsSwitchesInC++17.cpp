/*Initializer in for-statement

  in early C++, you had initialize i before 
  int i; //i is in the enclosing scope 
  for(i=0; i<n; ++i){
    ...
  } //i still will be in existence and can't create another variable called i 

  in C++98 
  for(int i=0; i<n; ++i){
    ... //i is local to the loop 
  }
  - this is encapsulation 
  - this makes code clearer, concise and safer
-------------------------------------------------------------------------------
Initializer in if statement 
------------------------------------------------------------------------------
- We often have situations where we want to check return value from function 
  before we do something. So this normally means we have to define a variable 
  to hold the returned value and then write a statement like 
  auto iter = begin(vec); 
  if(iter!=end(vec)){ //check container is not empty 
    ...
  }
- C++17 allows an initializer in an if statemt. So we can do what we did above 
  in single statement 
  if(auto iter=begin(vec); iter!=end(vec)) //check container is not empty 
  * This has similar advantages to the for loop Initializer 
  * iter is local to the if statement 
    - this includes the else block which corresponds to the if 

-------------------------------------------------------------------------------
Initializer in switch statement 
------------------------------------------------------------------------------
- older c++ 
  const char c=get_next_char();
  switch(c){
    ...
  }

- C++17 allows initializer in switch statement 
  switch(const char c=get_next_char(); c){ //again c is local to this switch G
    ...
  }
*/


#include <iostream> 
#include <vector>


using namespace std;

int main(){
  vector<int> vec{1,2,3,4,5};

  //older C++ 
  auto iter=begin(vec); 
  if(iter!=end(vec)){
    //safe to use iterator here 
    cout << "First element is: " << *iter << "\n";
  }

  //C++17 
  if(auto iter=begin(vec); iter!=end(vec)){
    //safe to use iterator 
    cout << "First element is: " << *iter << "\n";
  }

  //-----------------------------------------------------------------------------
  //switch demonstration 
  //-----------------------------------------------------------------------------
  char c; 
  int ws_count{0};
  const char *arr = "How much whitespace in\t here?";
  cout << "The text to process is \"" << arr << "\"" << endl; 
  for(int i=0; arr[i]; ++i){ //equivalent for(int i=0; arr[i]!='\0'; ++i), i.e., loop continues as long as it doesn't see 0 
    switch (const char c=arr[i]; c) {
      case ' ': //c is space character 
      case '\t': //c is tab character 
      case '\n': //c is new line character 
        ++ws_count; //increment white space count 
        break; 
      default: 
        break; 
    }    
  }
  cout << "The text contains " << ws_count << " whitespace characters" << "\n";

  /* 
  Falling thorugh case labels deliberately 
  - if there is no break at the end of a case label, the program flow "falls through" to the next label 
  -often this is useful as shown in above cases
  
  - Definition: Fall-through occurs when control flows from one case label to 
    the next without an intervening break, return, or goto. The statements in 
    the next case execute unintentionally (or intentionally) after the first 
    case.

  - Example (unintentional fall-through):
    * switch (x) { case 1: doA(); /* missing break *\ case 2: doB(); break; }
    * If x == 1, both doA() and doB() run.
  - Intentional fall-through (C++17+):
    * Use [[fallthrough]]; to mark deliberate fall-through and silence warnings:
    * switch (x) { case 1: doA(); [[fallthrough]]; case 2: doB(); break; }
  - Best practices:
    * End each case with break, return, or throw unless fall-through is 
      explicitly intended.
    * Prefer separate blocks or refactor shared logic into a helper function 
      to avoid ambiguous flow.
  - Compiler diagnostics:
    * Many compilers warn on fall-through (e.g., -Wimplicit-fallthrough in 
      GCC/Clang, /w34265 or code analysis in MSVC). Use [[fallthrough]] or add 
      comments recognized by your toolchain to indicate intent.
  - default case:
    * Always include default: (or exhaustively handle all enum values) to avoid 
      unhandled input. Apply the same rules about break/return.
  - Summary: Fall-through is when execution continues into the next case 
    unintentionally; prevent it with break/return, and if you mean it, annotate 
    with [[fallthrough]] for clarity and to satisfy compilers.

  Example where fallthrough case is not correct and leads to errors 
  -lets say you want to assign a vehicle based on where they work 
    switch(employee_location){
      case HEAD_OFFICE: 
        vehicle_type = Mercedes;
                                //no-break - fallthrough to next case       
      case SALES_OFFICE:
        vehicle_type = Peugeot;
                                //no-break - fallthrough to next case       
      case WAREHOUSE: 
        vehicle_type = truck; 
                                //All employees will have this vehicle_type        
    }
  - since there is no-break after checking employee office, it will fallthrough 
    and everyone gets assigned to truck. 
  */ 
//-----------------------------------------------------------------------------  
/*Fall-through attribute 
  - C++17 provides a [[fallthrough]] attribute 
  - this is used with an empty statement 
  - It indicates that the break statement is intentionally omitted 
  - The compiler will not give warning 
  - An attribute is simply an instruction to the compiler, and it can't change 
    the meaning of the code
  - To write an attribute, we put it inside a pair of square brackets, and the 
    language defines quite a few of these 
    switch(case c){
      case ' ':
        [[fallthrough]]; //fallthrough to next case. Not a mistake 
      case '\t':
        [[fallthrough]]; //fallthrough to next case. Not a mistake 
      case '\n':
        ++ws_count; 
        break;
    }
*/
  
  ws_count = 0; 
  //use of fallthrough attribute 
  for(int i=0; arr[i]; ++i){ //equivalent for(int i=0; arr[i]!='\0'; ++i), i.e., loop continues as long as it doesn't see 0 
    switch (const char c=arr[i]; c) {
      case ' ': //c is space character
        [[fallthrough]]; 
      case '\t': //c is tab character 
        [[fallthrough]]; 
      case '\n': //c is new line character 
        ++ws_count; //increment white space count 
        break; 
      default: 
        break; 
    }    
  }
  cout << "The text contains " << ws_count << " whitespace characters" << "\n";
}

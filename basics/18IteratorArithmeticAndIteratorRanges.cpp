#include <iostream> 
#include <vector>


using namespace std;

int main(){
    
  string str{"Hello"};
  /*Iterator arithmetic 
   - We cna perform arithmetic on iterators 
    * similar to pointers 
  */
  
  //Adding to an iterator moves it towards the back of the container 
  auto second = begin(str) + 1; 
  cout <<"second element: " << *second << "\n";
  
  //subtracting from an iterator moves it towards the front of the container 
  auto last = end(str) - 1; //iterator to last element  
  cout <<"last element: " << *last << "\n";
  

  //end()-begin() gives the number of elements 
  auto mid = begin(str) + (end(str) - begin(str))/2; //iterator to middle element 
  cout <<"middle element: " << *mid << "\n" ;

  cout << "number of elements: " << end(str)-begin(str) << "\n";
  
  //Iterator arithmetic functions 
  //having bare numbers like begin(str)+1 in code is generally not a good idea 
  //as it not clear what they mean so it's better to use iterator functions 
  //next() takes an iterator and returns the following iterator 
  auto second1 = next(begin(str)); //returns an iterator to second element 
  if(second1!=end(str)){//generally good idea to check if its valid 
    cout <<"second element: " << *second1 <<"\n";
  }
  //prev() takes an iterator and returns the previous iterator 
  auto last1 = prev(end(str)); //returns iterator to last element 
  if(last!=end(str)){
    cout <<"last element: " << *last1 << "\n";
  }
  //distance() returns the number of steps needed to go from its first argument
  //to its second argument 
  auto num_steps = distance(begin(str), end(str)); //returns the number of elements 
  cout << "num steps: " << num_steps << "\n";

  //advance() moves an iterator by its second argument 
  auto mid1 = begin(str);
  advance(mid1, distance(begin(str), end(str))/2); // mid is iterator to middle  
  if(mid1!=end(str)){
    cout << "mid1: " << *mid1 << "its index: " << distance(begin(str), mid1) << "\n";
  }
  
  /*Half-open range 
    - you will often see the work half-open range when we read about iterators 
    - imagine we have loop with an integer loop counter 
      for(int i=0; i<10; ++i) 
      - In the loop body, 'i' has an allowed range of values: 0,1,2,...,9 but not 10 
      - This is known as a "half-open" range 
      - It is written [0, 10) 
        * i>=0 must be true and i<10 must be true 
        * i==10 is not allowed 

    Iterator ranges 
    - The iterators returned by begin() and end() define an iterator range 
    - if we have a loop with an iterator as loop counter 
      for(auto it=begin(str); it!=end(str); ++it) 
      - In the loop body 'it' has an allowed range of values 
        * begin(), begin()+1, begin()+2,.. but not end(). This is a "half-open range" 
        * it>=begin() must be true and it<end() must be true 
        * it==end() is not allowed 
  */
}

/*
------------------------------
C++17 Structured Binding
------------------------------
- C++17 introduced the structured binding
- This is an easy way to access data structures
- In a single statement, we
  * Declare local variables
  * Bind them to members of a compound data structure
  * The types are deduced by the compiler
- With auto in C++11, the compiler can deduce the types of a single variable
given a scalar initializer
auto i=42; //variable i has type int, initial value 42
- in C++17, this has been extended to work with multiple variables and a
compound initializer
  * Each variable will be initialized from a member of a compound value
  * The compiler deduces the type of each variable
- For example, we can initialize two variables from an std::pair
 pair p(1,3,142); //std::pair<int, double>
- The compiler will deduce the type of each variable from the corresponding
element in the intializer
  auto [i,d]=p; //variable i has type int, initial value 1
                //variable d has type double, initial value 3.142

---------------------------------
Loops and Structured Bindings
---------------------------------
- Structured bindings can make map loops more readable
//c++11/14
for(auto el : scores){
  cout << el.first << "has score of" << el.second << endl;
}

//c++17
 for(auto [name,score] : scores){
   cout << name << "has a score of " << score << endl;
 }

------------------------------------
Checking std::map insert() in C++17
------------------------------------
- With a structured binding, checking the return value from insert() is much
simple
 //returns std::pair<std::map<std::string, int>::iterator, bool>
 auto [iter, success] = scores.insert(make_pair("Graham"s, 66));

 if(success){
  cout << "Inserted the new elements\n";
 }else{
  auto [name, score]=*iter;
  cout << "insert failed";
  cout << "existing element with name " << name << " and score" << end;
 }

---------------------------
insert_or_assign()
---------------------------
- C++17 provides insert_or_assign()
- This takes two arguments
  * The new element's key
  * Its value
- The returned value is an std::pair
  * The first member is an iterator to the element
    - The new element on insertion
    - The old element on assignment
  * The second member is a bool
    - true or insertion
    - false on assignment

- Using C++17 features
- Structured binding
- Initializer in if statement
  if(auto [element, inserted] = scores.insert_or_assign("Graham", 66);,
inserted){
    //The new element was inserted
  }
  else{
    //An existing element was modified
  }
*/

#include <iostream>
#include <map>

using namespace std;

int main() {
  pair p(1, 3.142); // std::pair<int, double)
  auto [i, d] = p;  // i int, d double with structured binding
  cout << "i = " << i << ", d = " << d << "\n";

  map<string, int> scores; // creates an empty std::map
  scores.insert(make_pair("Maybelline", 82));
  scores.insert({"Graham", 78}); // Add some elements to it

  cout << "Map elements printed using structured binding: \n";
  for (const auto &[name, score] : scores) {
    cout << name << " has a score of " << score << "\n";
  }
  // returns std::pair<std::map<std::string, int>::iterator, bool>
  auto [iter, success] = scores.insert(make_pair("Graham"s, 66));

  if (success) {
    cout << "Inserted the new elements\n";
  } else {
    auto [name, score] = *iter; // get the memebers of the element pair
    cout << "insert failed: ";
    cout << "existing element with name " << name << " and score " << score
         << "\n";
  }

  cout << "\nThe demonstration of insert_or_assign() \n";
  auto [iter1, success1] = scores.insert_or_assign("Graham"s, 66);
  auto [name1, score1] = *iter1;
  if (success1) {
    cout << "Inserted the new elements with name " << name1 << " and score "
         << score1 << "\n";
  } else {
    cout << "insert failed: ";
    cout << "existing element with name " << name1 << " now has score "
         << score1 << "\n";
  }
}

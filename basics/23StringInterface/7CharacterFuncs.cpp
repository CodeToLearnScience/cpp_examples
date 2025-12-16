/*-----------------------------
Character functions 
------------------------------- 
- The C++ standard library has a number of Character functions which are 
  inherited from C 
- These are defined in <cctype> and operate on chars 
- Most useful are 
  * isdigit(c); //Returns true if c is digit (0-9) 
  * islower(c); //Returns true if c is lower case (a-z) 
  * isupper(c); //Returns true if c is upper case (A-Z) 
  * isspace(c); //Returns true if c is a whitespace Character (space, tab, etc) 
  * ispunct(c); //Returns true if c is a punctuation character(?, !, ., etc) 
*/

#include <iostream> 
#include <cctype> 

using namespace std; 

//return true if input starts with 'Y' or 'y'
bool yes_or_no(const string& input){
  char c=input[0]; 
  if(toupper(c)=='Y'){
    return true;
  }
  return false; 
}

//case-insensitive string equality 
bool equal_strings(const string& lhs, const string& rhs){
  if(lhs.size()!=rhs.size()){
    return false; 
  }
  auto lit=cbegin(lhs);
  auto rit=cbegin(rhs);

  while(lit!=cend(lhs) && rit!=cend(rhs)){//we could have written for-loop 
    if(toupper(*lit)!=toupper(*rit))
      return false; 
    ++lit;
    ++rit;
  }
  return true; 
}

int main(){
  
  string hello{"Hello, world!"}; 

  for (auto c: hello){
    if(isupper(c)) cout << c << " is an upper case letter\n";
    if(islower(c)) cout << c << " is an lower case letter\n";
    if(ispunct(c)) cout << c << " is a punctuation character\n";
    if(isspace(c)) cout << "\'" << c << "\'" << " is a whitespace character\n";
  }
/*-----------------------
  tolower() and toupper()
  -----------------------
  - If you have used Linux, or possibly some command line programs on Windows 
    or DOS, you may have seen programs that ask you to type in anything with "y"
    to confirm that you want to proceed
    The function "yes_or_no" does that 
*/
  string input; 
  cout << "Do you want to enter a string which starts with Y or y?" << endl; 
  cin >> input; 
  if(yes_or_no(input))
    cout << "Evidently you do!\n"; //raw string to avoid putting backslash aroung " 
  else 
    cout <<R"(I will take that as a "no"!)" << endl; 

/*-------------------------------------- 
Case sensitivity and string comparisons 
----------------------------------------
- operations on std::string are case sensitive 
- There is no direct support for doing a case-insensitive comparisons of two 
  strings 
- compiler implementations often provide functions which perform case-insensitive 
  comparisons of C-style strings 
  * stricmp on Windows 
  * strcasecmp on Unix 
- These are not standard, not portable and do not directly support std::string 
- The simplest solution if we want to compare C++ strings without worrying about 
  case is to convert all strings to a single case before comparing them 
  for(auto& c: str)
    c=toupper(c) 
  * This changes string and removes the original case information 
  * If we need to preserve this, in-place conversion is not acceptable 
  * we can make copy which we convert to single-case 
  * Alternatively, we can write our own comparison function as follows 
  ----------------------
  equal_strings function 
  ----------------------
  * Our function should have the same interface as the built-in operator 
  * Take two strings by const reference and return a bool 
    //case-insensitive string equlity. Returns true of lhs and rhs are equl, 
    //otherwise false 
    bool equal_strings(const string& lhs, const string& rhs){
    }
    - It will do case-insensitive comparison for each corresponding character 
      in the two strings. 
    - First we compare the lengths of the strings 
    - If lengths differ, the strings are not equal 
    //If the two strings have different lengths, return false 
    if(lhs.size!=rhs.size(){
      return false;
    }
    - Then we look at each corresponding character in the two strings and 
      compare them 
      auto lit = cbegin(lhs); 
      auto rit = cbegin(rhs); 
      while (lit!=end(lhs) && rit!=end(rhs)){
        if(toupper(*lit)!=toupper(*rit)) 
          return false;
        ++lit; 
        ++rit; 
      }
      return true; 
  */    
  //demonstration of equal_strings: case-insensitive  
  string a{"one"}, b{"two"}, c{"One"};
  cout << "Using library == operator\n"; 
  cout << a << " and " << b << " are " << (a==b ? "" : "not ") << "equal\n";
  cout << b << " and " << c << " are " << (b==c ? "" : "not ") << "equal\n";
  cout << a << " and " << c << " are " << (a==c ? "" : "not ") << "equal\n";
  
  cout << "\nUsing equal_strings()\n";
  cout << a << " and " << b << " are " << (equal_strings(a,b) ? "" : "not ") << "equal\n";
  cout << b << " and " << c << " are " << (equal_strings(b,c) ? "" : "not ") << "equal\n";
  cout << a << " and " << c << " are " << (equal_strings(c,a) ? "" : "not ") << "equal\n";
}

#include <iostream> 

using namespace std::literals; //C++14 literals have their own namespace 
int main(){

  /*c-style string literal. The traditional string literal is an array of const 
  - char, terminated by a null character 
  - very limited range of operations 
  - only compatible with arrays of the same length 
  */ 
  const char *cca="hello world!"; // c-style string-null-terminated array of const char 

  /*String literal 
   - From C++14, we can create std::string literals 
   - We add 's' after the closing double quote
  */

  std::string str = "Hello, string!"s;
  std::cout << "str: " << str << "\n";
  //supports all std::string operations 
  std::cout << "string literal: " << "hello"s+",world!"s << "\n"; //just adding "hello " + "world" doesn't work without "s 
  //can be used anywhere that expects as std::string object 

  /* 
  string literals and escape characters 
  - in string literal certain characters can be escaped. This gives them a 
    different meaning 
  - This is done by putting a backlash \ in front of them 
    \n - newline character in string literal (not character 'n') 
    \" - double quote in a string literal (not string terminator) 

  - <a href="file">C:\"Program Files"\</a>\n 
  - to write this as string literal 
  */
  std::string url = "<a href=\"file\">C:\\\"Program Files\"\\</a>\\n"s;
  std::cout <<"url: " << url << "\n";

  //Raw string literals 
  //C++11's raw string literals avoid "backlashitis" 
  //We put the string literal inside R"(..)"
  //Raw string literal with unescaped characters 
  std::string url1=R"(<a href="file">C:\"Program Files"\</a>\n)";
  
  std::cout << "url1: " << url1 << "\n";

  //If the string contains )" we need to add a delimiter otherwise it will not be processed as in previous example 
  std::string delimited_url=R"x(<a href="file">C:\"Program Files (x86)"\</a>\n)x";
  std::cout << "delimited url: " << delimited_url << "\n";
  return 0; 
}

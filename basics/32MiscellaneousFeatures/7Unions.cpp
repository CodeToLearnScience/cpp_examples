/*
-----------------
Unions
-----------------
- C++ inherited unions from C
- A union is a compound data structure
  * Each member must have a distinct type
  * All the members are stored at the same address
  * Only one member can be in use at a time

-------------------------
Memory Layout
-------------------------

┌─────────────────────────────────────────────────────────┐
│ struct Token {                                          │
│   char c;                                               │
│   int i;                                                │
│   double d;                                             │
│ };                                                      │
└─────────────────────────────────────────────────────────┘

Memory Layout:
┌────┬──────┬──────┬──────┬──────┬──────────────────────┐
│ c  │      │      │      │  i   │             d        │
└────┴──────┴──────┴──────┴──────┴──────────────────────┘
<-c-><-  Padding bytes  -><- i  -><-------   d  -------->

- In struct, char will be stored at the beginning of struct memory. The int
member will follow the character, and double will come after int. The compiler
may also put in some so-called "padding" bytes. That means that the program will
access the character value as a word and not as a byte and that's much more
efficient. Depending on the architecture, there could be some padding bytes
after int as well

┌─────────────────────────────────────┐
│ union Token {                       │
│   char c;                           │
│   int i;                            │
│   double d;                         │
│ };                                  │
└─────────────────────────────────────┘

Memory Layout (Overlapping):
┌─────────┬─────────┬─────────────────┐
│         │         │                 │
└─────────┴─────────┴─────────────────┘
<--------->
    c
<------------------->
         i
<------------------------------------->
                  d

  ← c (1 byte) →
  ← i (4 bytes) ────→
  ← d (8 bytes) ──────────────→

Total Size: 8 bytes (largest member)

- In case of union with same members, the character will again begin at the
start of the union's memory. The int will also begin at the start of the union's
memory, and its storage will overlap the character storage and the double will
also begin at the start of the union's memory and its storage will overlap the
character and the int
You may think its a trick for saving memory. The main application of unions is
if you are processing data, which could be one of several types and that comes
in useful if you are parsing source code, for example, or processing data that
you have received over the network

----------------------------
Union Characteristics
----------------------------
- All the members of a union are public by default
- In older C++, the members must be simple data types
  * No special member functions
  * This was relaxed in C++11
- Unions can have member functions, but not virtual member functions
- Unions cannot be used as base or derived classes

--------------------
Union Usage
--------------------
- If we assign to the char member, that member is now "in use"
  * only one member can be in use at any one time
  * The other members have undefined values
  * It is only safe to read from a member if it is currently in use

------------------
Tagged Union
------------------
- This use of unions is highly error-prone
  * The programmer has to remember which type is in use
- Unions can be made safer by adding a "tag" member. This is an extra member,
which will just keep track of which member is in use
- This indicates which member is in use
- This is known as a "tagged union"

-------------------------
Wrapped Tagged Union
-------------------------
- A tagged union requires the programmer to check before accessing a member
- The programmer must also set the type when bringing a member into use
- For greater safety, wrap the tagged union inside a class
  * The union is a private member of the class
  * Union can only be accessed through the class's public member functions
  * These perform the necessary setting and checking of the tag member
  * The member functions can perform suitable error handling, e.g, return a null
    pointer or throw an exception
- This enforces correct use of union

-------------------
C++17 std::variant
-------------------
- C++17 provides an std::variant type
- Similar to a wrapped tagged union, but
  * Type-safe
  * Can have different "alternatives" with the same type
  * Automatically calls constructors and destructors, when requied
  * simpler to use
- Templated type defined in <variant>
- The template parameters give the member types or "alternatives"

  variant<char, int, double> v;

  //Anologous to
  union{
    char c;
    int i;
    double d;
  }v;

---------------------------------
Accessing Data in a Variant
---------------------------------
- We can assign to a variant

  variant<char, int, double> v;
  v = 'Z';    //char alternatives

- The deduced type of the argument is used to choose the alternative
- To get an alternative from a variant, we call std::get() like tuples

    //get by type (if unique)
    get<char>(v);

    //get by index
    get<0>(v);

-----------------------------
std::holds_alternative()
-----------------------------
- We can all std::holds_alternative() to check whether an alternative is in use

  if(holds_alternative<double>(v)) //returns bool
  {
      cout << get<double>(v) << endl; //true if the double alternative in use
  }
  else{
      cout << "Double alternative is no in use\n";
  }

----------------------------------------------
Applications of Unions and std::variant
----------------------------------------------
- Parsing
  * source code where a variable can have one of several types
  * Configuration (INI) file where a parameter can only be a string, a number or
  a Boolean
- Language Implementation
  * An object can have one of several types depending on how it is used("duck
typing") which means object can have several types, and the type which it has
  depends on how it is used
- Return values
  * The result of a computation which can have outcomes of differnt types
  * Return a unior or variant for error handling
    - Result object if successful
    - Error code on failure
- Polymorphism
  * virtual functions implementation
*/

#include <exception>
#include <iostream>
#include <stdexcept>
#include <variant>

using namespace std;

union Token {
  // members are public by default
  char c;
  int i;
  double d;
};

namespace tagged_union {

// TokenType member has to be outside the union as shown below
enum class TokenType { Char, Int, Double };

// or
struct TokenType1 {
  Token token;
  TokenType type; //"Tag" filed to indicate which member is in use
};

union Token {
  char c;
  int i;
  double d;
  TokenType type;
};

void example() {
  Token token;
  token.type = TokenType::Char; // char member is in use
  token.c = 'Z';

  // check if safe to access double member
  if (token.type == TokenType::Double) {
    cout << token.d << "\n";
  } else {
    cout << "Double member not in use\n";
  }
}

class TokenWrapper {
  Token token;

public:
  void set_char(char c) {
    token.type = TokenType::Char;
    token.c = c;
  }

  double get_double() {
    if (token.type == TokenType::Double) {
      return token.d;
    } else {
      throw std::invalid_argument("Double member not in use\n");
    }
  }
  // similarly we can implement other member functions to set and get
};

void token_wrapped_union() {
  TokenWrapper tw;
  tw.set_char('Z');
  // check if safe to access double member
  try {
    double d = tw.get_double();
    cout << d << "\n";
  } catch (std::exception &e) {
    cout << "Caught exception: " << e.what() << "\n";
  }
}
} // namespace tagged_union

namespace std_variant {
void example() {
  variant<char, int, double> v;
  v = 'Z'; // char member is in use
  if (holds_alternative<double>(v)) {
    cout << get<double>(v) << "\n";

  } else {
    cout << "Double member not in use\n";
  }
}
} // namespace std_variant

int main() {
  Token token;
  token.c = 'Z';           // char member is in use
  cout << token.d << "\n"; // double member not in use - had undefined value
  /*
  What will happen is that the program tries to interpret the member used by the
  union as a double. The first byte of this memory will contain the ASCII code
  for capital 'Z' and the rest of the bytes will contain - well, who knows? So
  we will probably get some kind of garbage number
   */

  cout << "--------------Tagged union---------------\n";
  tagged_union::example();
  /* But there is still a problem: we have to rely on the programmer who
   * assigned to the character member. We have to assume that they also
   * remembered to set the token type. So there is still a scope for human error
   */

  cout << "--------------std variant---------------\n";
  std_variant::example();
}

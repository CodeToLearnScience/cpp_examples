/*
--------------------------------
Member Functions and Inheritance

Inheriting Member Functions
--------------------------------
- A child class "inherits" all the non-private member functions of its parent
class

 class Vehicle{
   public:
     void start() {cout << "Engine started:";}
 };

 class Aeroplane: public Vehicle{
   public:
     /// void start(); //Inherited from Vehicle ///
 };

 plane.start(); //calls start() on an Aeroplane object. Prints out "Engine
   // started"

--------------------------------
Reimplementing Member Functions
--------------------------------
- A child class can re-implement the parent class's member functions
- To make them more appropriate for the child
  class Aeroplane: public Vehicle{
    public:
      void start(){
        cout << "Carrying out checks...";
        cout << "Ready for take-off!";
      }
  };

  plane.start(); //prints out "Carrying out checks...Ready to take-off!"

---------------------------
Extending Member Functions
---------------------------
- The child class can also extend the parent's member functions

  class Aeroplane: public Vehicle{
    public:
    void start(){
      cout << "Carrying out checks...";
      Vehicle::start(); //calls a member function of the base class
      cout << "Ready for take-off!";
    }
  };

-----------------------------------------------------------------------------
- You might have observed, we din't say that the child inherits public member
functions. We said that the child inherits member functions which are not
private. The reason is that there are actually three access specifiers in C++
-----------------------------------------------------------------------------
-------------------
Public access
-------------------
- A public member of a class is accessible from any part of the code
  * It is part of the class's interface
- A child class will have access to all its parent's public members
- A child class doesn't have access to its parent's private members
- Often, we want to write member functions which are not part of the class's
public interface, but are available to child classes. That is sometimes its
useful to have member functions in the parent, which can be used by child
classes but not by any other code
  * These member functions are part of the class's implementation. And to do
    that we used Protected access

--------------------------
Protected access
--------------------------
- A parent class can make its members available to it's children, but not to
other code
  * This maintains encapsulation
- To do this, use the protected access specifier
  protected:
    int secret;             //protected data member - not that useful
    void kids_only();       //can only be called by children of this class
- You can make data members protected but generally that is not useful so mostly
we make member functions protected
*/

#include <iostream>

using namespace std;

class Vehicle {
public:
  void start() { cout << "Engine started:"; }
};

class Aeroplane : public Vehicle {
public:
  /// void start(); //Inherited from Vehicle ///
};

class Aeroplane1 : public Vehicle {
public:
  void start() {
    cout << "Carrying out checks...";
    cout << "Ready for take-off!";
  }
};

class Aeroplane2 : public Vehicle {
public:
  void start() {
    cout << "Carrying out checks...";
    Vehicle::start(); // calls a member function of the base class
    cout << "Ready for take-off!";
  }
};

/// demonstration of protected access
class Vehicle1 {
protected:
  void kids_only(); // can only be called by this class and its children
};

class Aeroplane3 : public Vehicle1 {
public:
  void do_something() { kids_only(); }
};

int main() {

  Aeroplane plane;
  plane.start(); // calls start() on an Aeroplane object. Prints out "Engine
  // started"
  cout << "\n\n";

  Aeroplane1 plane1;
  plane1.start(); // Calls start() on an Aeroplane1 object
  cout << "\n\n";

  Aeroplane2 plane2;
  plane2.start(); // Calls start() on an Aeroplane1 object
  cout << "\n\n";

  Vehicle1 vehicle1;
  // vehicle1.kids_only(); //cannot be called by "outsider" code
}

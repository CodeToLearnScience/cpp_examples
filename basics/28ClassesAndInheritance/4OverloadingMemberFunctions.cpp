/*
------------------------------
Overloading Member Functions
------------------------------
- We can overload inherited Member Functions
- We write a new Member function which has the same name but a different
signature

  class Vehicle{
    public:
      void accelerate(){}
  };

  class Aeroplane: public{
    public:
      void accelerate(int height); //overload of accelerate
  }

-----------------------------------------
Hidden Member Functions
-----------------------------------------
- If we overload an inherited function in the child class, it will "hide" all
the other inherited Member functions with that name
  * Those functions cannot be called on the child class
- This is inconsistent with OO design principles
  * The parent class represents the interface of the hierarchy
  * Child classes should extend the interface, not obscure it

----------------------------------------
Hidden Member Functions - Older Solution
----------------------------------------
- One Solution is to define the inherited functions in the child class
  * We add an accelerate Member functionto Aeroplane that calls the Vehicle
    Member function
  * This requires one Member function in Aeroplane for each hidden version of
    the function

    class Aeroplane : public Vehicle{
      void accelerate(){Vehicle::accelerate();} //call parent version of
                                                //accelerate()
      void accelerate(int height); //Aeroplane's overload of accelerate
    };
- However, in a big hierarchy, that is going to be a lot of work and if the base
class keeps changing, it is going to be a bit of nightmare keeping this up-to
date

----------------------------------------
Hidden Member Functions - Modern Solution
----------------------------------------
- From C++11, we can tell the child class to "use" the parent's version

  using Vehicle::accelerate;   //Make Vehicle's version of accelerate() availble
                               //here
  void accelerate(int height); //Aeroplane's overload of accelerate()
- This will make all the hidden versions of the function availble in the child
class

*/

#include <iostream>

using namespace std;

class Vehicle {
public:
  void accelerate() { cout << "Increasing speed: "; }
};

class Aeroplane : public Vehicle {
public:
  void accelerate(int height) {
    cout << "Accelerating at a height of: " << height;
  }
};

class Aeroplane1 : public Vehicle {
public:
  void accelerate() {
    Vehicle::accelerate();
  } // call parent version of accelerate
  void accelerate(int height) {
    cout << "Accelerating at a height of: " << height;
  }
};

/// Modern C++11 solution for hidden Member Functions
class Aeroplane2 : public Vehicle {
public:
  using Vehicle::accelerate;
  void accelerate(int height) {
    cout << "Accelerating at a height of: " << height;
  }
};

int main() {
  Aeroplane plane;
  plane.accelerate(1000);
  cout << "\n";

  /*There is one drawback because C++ is designed many many years ago. This
  parent class function, which takes no arguments, is inherited by this
  Aeroplane class But you cannot actually call it from outside the class. Even
  though the class has supposedly inherited it */
  // plane.accelerate();

  // now with inherited function defined inside child class it works
  Aeroplane1 plane1;
  plane1.accelerate();

  cout << "\n\n";
  Aeroplane2 plane2;
  plane2.accelerate();
}

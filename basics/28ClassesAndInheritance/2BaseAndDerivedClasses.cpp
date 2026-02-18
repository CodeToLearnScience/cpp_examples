/*
--------------------------------------
Base class and Derived class Examples
--------------------------------------
- We will create a simple hierarchy which has a Vehicle class and an Aeroplane
class
class Vehicle{ //this will be the base class
  int max_speed;
};

class Aeroplane{ //this will be the derived class
  int max_height;
};

----------------------
Deriving a class
----------------------
- To define a derived class, we put a colon : after its name, followed by the
public keyword and the name of the base class

class Aeroplane : public Vehicle{
};

- The derived class will be able to call the non-private member functions of the
base class
- It can also access any non-private data members
- Optionally, the derived class can replace the base class's member functions
with its own versions

----------------------------
Derived Class Memory Layout
----------------------
- A derived class object is stored in memory as a base class object followed by
the derived class part
When a derived class object is created, the base class's constructor is called
first, then the derived class's constructor
- When it is destroyed, the derived class's destructor is called before the base
class's

Vehicle
<----------->
---------------------------------
|             |                 |
---------------------------------
<-------------------------------->
           Aeroplane

----------------
Constructors
----------------
- The derived class constructor calls the base class's constructor to initialize
the base class part of the object
- We can use the same initializer syntax as for a class member

  class Aeroplane : Vehicle{
    Aeroplane():Vehicle(){} //initialize the vehicle part of the object
  };

----------------------------
Constructors with arguments
----------------------------
- If effect, each class initializes its own members

  class Vehicle{
    Vehicle(int max_speed) : max_speed(max_speed){}
    ...
  };

  class Aeroplane{
    //initialize the vehicle part of the object, then initialize max_height
    Aeroplane(int max_speed, int max_height) : Vehicle(max_speed),
      max_height(max_height){}
  };

---------------------------------------------
Deriving from a Derived Class
---------------------------------------------
- We can use a derived class as the base class of another derived class

  class Aeroplane : public Vehicle{
    ...
  };

  class FighterPlane : public Aeroplane{ //more specialized Aeroplane
   ...
  };

- Aeroplane is the "parent" class of FighterPlane
- FighterPlane is the "child" class of Aeroplane
- Vehicle is the "parent" class of Aeroplane
- Aeroplane is the "child" class of Vehicle
*/

#include <iostream>

using namespace std;

class Vehicle {
  int max_speed;

public:
  Vehicle(int max_speed) : max_speed(max_speed) {
    cout << "Vehicle constructor\n";
  }
};

class Aeroplane : public Vehicle {
  int max_height;

public:
  Aeroplane(int max_height, int max_speed)
      : Vehicle(max_speed), max_height(max_height) {
    cout << "Aeroplane constructor\n";
  }
};

int main() {

  cout << "Creating Vehicle object\n";
  Vehicle vehicle(10);
  cout << "Creating Aeroplane object\n";
  Aeroplane(40000, 500);
}

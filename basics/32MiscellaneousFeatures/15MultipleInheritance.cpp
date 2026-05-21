/*
----------------------------------
Multiple Inheritance
----------------------------------
- In multiple inheritance, a derived class has more than one parent
- Multiple inheritance is controversial!
  * Adds complexity
  * Many programmers and OO designers dislike it
  * Some languages do not support it (ex. Java)
- However, multiple inheritance can be useful for writing "mix-in" classes. That
is if you have two classes which represent entirely separate concepts. For ex,
one class which interacts with files and another class which interacts with
users. You could "mix" these into a single class which allows users to interact
with files.

-----------------------------------
Multiple Inheritance Hierarchy
-----------------------------------
- In multiple inheritance, a derived class has more than one parent
- This represents a class which is a combination of different entities
  * A mouse class needs to respond to UI events, but also communicate with
    hardware


+------------------+          +------------------+
|                  |          |                  |
|  Touch Responder |          | Hardware Device  |
|                  |          |                  |
+------------------+          +------------------+
         \                            /
          \                          /
           \                        /
            v                      v
                  +----------+
                  |          |
                  |  Mouse   |
                  |          |
                  +----------+

- So we could write a Mouse class which inherits from the TouchResponder and
also from the HardwareDevice. So this can respond to mouse button clicks, and
also communicate with the physical mouse

-------------------------------
Multiple Inheritance
-------------------------------
- The syntax is an extension of single inheritance

    class HardwareDevice; //Hardware class
    class TouchResponder; //User interface class

    //Mouse class inherits from both HardwareDevice and TouchResponder
    class Mouse: public HardwareDevice, TouchResponder{
      ..
    }

-------------------------------------
Multiple Inheritance Memory Layout
-------------------------------------
- A derived class object is stored in memory as the base class objects followed
by the derived class part
  * The base class objects are stored in the order they were listed
  * The base classes's constructor are called in the order they were listed,
    then the derive class's constructor called
  * The destructors are called in the reverse order of the constructors

        <---HardwareDevice---><---TouchResponder--->
         -------------------- --------------------- -------------------
        |                    |                     |                   |
         -------------------- --------------------- -------------------
        <-------------------------Mouse-------------------------------->

------------------------
Class Scope
------------------------
- The derived class inherits the member of all its parents
    class HardwareDevice{  //Hardware class
      public:
        void get_data();
    };

    class TouchResponder{  //User interaction class
    public:
      bool touch_down();
    };

    void Mouse::process(){  //member function in Mouse class
      if(touch_down())      //Mouse inherits touch_down() from TouchResponder
          get_data();       //Mouse inherits get_data() from HardwareDevice
    }

- If we call an inherited member function, its name must only be defined in one
parent
 bool HardwareDevice::initialize(Params&); //HardwareDevice defines initialize()
 void TouchResponder::initialize();        //TouchResponder defines initialize()

 Mouse mouse;
 mouse.initialize();  //Error - ambiguous call

- This can be avoided by adding a forwarding function to the child

    bool Mouse::initialize(Params& params){
      TouchResponder::initialize();
      return HardwareDevice::initialize(params);
    }

    Mouse mouse;
    Params params;
    mouse.initialize(params); //Ok
*/

#include <iostream>

using namespace std;
// hardware class
class HardwareDevice {};

// user interface class
class TouchResponder {};

// classes which inherit from both HardwareDevice and TouchResponder
class Mouse : public HardwareDevice, TouchResponder {};
class Keyboard : public HardwareDevice, TouchResponder {};
class TouchScreen : public HardwareDevice, TouchResponder {};

namespace multiple_inheritance {
struct Params {};

// hardware class
class HardwareDevice {
public:
  HardwareDevice() { cout << "Calling HardwareDevice constructor\n"; };
  ~HardwareDevice() { cout << "Calling HardwareDevice destructor\n"; };
  bool initialize(Params &) {
    cout << "Calling HardwareDevice::initialize()\n";
    return true;
  }
  void get_data() { cout << "Calling HardwareDevice::get_data()\n"; }
};

class TouchResponder {
public:
  TouchResponder() { cout << "Calling TouchResponder constructor\n"; };
  ~TouchResponder() { cout << "Calling TouchResponder destructor\n"; };
  void initialize() { cout << "Calling TouchResponder::initialize()\n"; }
  bool touch_down() {
    cout << "Calling TouchResponder::touch_down()\n";
    return true;
  }
};

class Mouse : public HardwareDevice, TouchResponder {
public:
  Mouse() { cout << "Calling Mouse constructor\n"; }
  ~Mouse() { cout << "Calling Mouse destructor\n"; }
  void process() {
    if (touch_down()) {
      get_data();
    }
  }

  bool initialize(Params &params) {
    cout << "Calling Mouse::initialize()\n";
    HardwareDevice::initialize(params);
    TouchResponder::initialize();
    return true;
  }
};

void example() {
  Mouse mouse;
  mouse.process();
  Params params;
  mouse.initialize(params);
}
} // namespace multiple_inheritance

int main() {
  Mouse mouse;

  multiple_inheritance::example();
}

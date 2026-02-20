/*
--------------------------------------
Base Class and Modelling
--------------------------------------
- Typically, base classes model abstract concepts such as "shape" or "vehicle"
- Concrete derived classes model concrete entities such as "circle" or
"aeroplane"

--------------------------------------------
Interface and Implementation
--------------------------------------------
- The base class is the interface to the class hierarchy
- Its public virtual member functions provide all the functionality that is
common to the hierarchy
  * Any Shape object can be drawn, rotated, etc
- The derived classes override these virtual functions. We are going to
implement them in a way which will be specific to that particular, concrete
class
  * A Circle object can draw a circle shape, rotate it, etc

-----------------------------------------
Virtual Functions in Base Class
-----------------------------------------
- Often, the base class's virtual member functions  cannot do anything useful
  * Each derived class will implement the functionality as appropriate
- These member functions can be left empty
- Or we can use C++ syntax to indicate they are not implemented here
- This helps express the idea of base class as interface

-----------------------------------
Pure virtual function
-----------------------------------
- We can make the base class's virtual functions "pure virtual"
- This is done by putting "=0" instead of the function body

  class Shape{
    public:
      virtual void draw() = 0; //draw() is a pure virtual function
  };

- This means that Shape does not implement draw(). It also means that the base
class Shape is an abstract base class, so we cannot create any objects
- This makes it clear that the virtual function

----------------------
Abstract Base Class
----------------------
- A class with a pure virtual member function cannot be instantiated

  Shape shape; //Error: cannot declare shape to be of abstract type

- THis is known as an "abstract base class"
  * Similar to an "interface" in other languages
- If we derive from an abstract base class, we must override all its pure
virtual functions
  * Otherwise, our derived class will also be an abstract

---------------------------
Object Slicing
---------------------------
- If we have a function that takes a base class object by value

    void draw_shape(Shape s); //Function taking shape by value

- And we pass a derived class object to it

    draw_shape(circle); //Pass derived class object by value as a Shape

- This will call Shape's copy constructor
  * s will be a copy of the Shape object
  * In effect, Circle part of the argument has has been "sliced off". That is in
    a way Circle part is removed
- This is known as "object slicing"

----------------------------------------
Abstract Base Class as Function Argument
----------------------------------------
- An abstract base class cannot be passed by value
  //Does not compile - cannot declare parameter of abstract type
  void draw_shape(Shape s);
- It can only be passed by reference or by address
- In the function body, dynamic binding will be used

  void draw_shape(const Shape& s){
    s.draw(); //Uses dynamic binding to call Circle::draw(), etc
  }
*/

#include <iostream>

using namespace std;

namespace abc_example {
class Shape {
public:
  virtual void draw() const = 0; // pure virtual member function
};

class Circle : public Shape {
public:
  void draw() const override { cout << "Drawing a circle...\n"; }
};

class Triangle : public Shape {
public:
  void draw() const override { cout << "Drawing a triangle...\n"; }
};

} // namespace abc_example

namespace object_slicing_example {
class Shape {
public:
  virtual void draw() const {
    cout << "Shape::draw()\n"; // empty virtual function
  }
};

class Circle : public Shape {
public:
  void draw() const override { cout << "Drawing a circle...\n"; }
};

// Function taking base class by value
void draw_shape(Shape s) {
  s.draw();     // Always call Shape's draw()
  (&s)->draw(); // Even if we call by reference
  // In both cases we get Shape::draw(), that means the dynamic type of the
  // variable s is actually a Shape class. And that is becasue the copy
  // constructor for Shape was called
}

void example() {
  Circle circle;
  draw_shape(circle);
}
} // namespace object_slicing_example
namespace example_pure_virtual {
class Shape {
public:
  /*virtual void draw() const {
    cout << "Shape::draw()\n"; // empty virtual function
  }*/
  virtual void draw() const = 0;
};

class Circle : public Shape {
public:
  void draw() const override { cout << "Drawing a circle...\n"; }
};

// Function taking base class by reference
void draw_shape(const Shape &s) {
  s.draw(); // Always call actaul object's draw(): here Circle
  (&s)->draw();
  // because we have draw as pure virtual, we cannot pass Shape by value, it has
  // to be by pointer or reference And now, the draw function of actual object
  // passed will be called. By using dynamic binding
}

void example() {
  Circle circle;
  draw_shape(circle);
}
} // namespace example_pure_virtual
int main() {

  // Shape shape; //Error: does not compile
  object_slicing_example::example();
  example_pure_virtual::example();
}

/*
------------------------
Static Binding
------------------------
- Normally when we call a member function of an object, the compiler will decide
which function is called
- This is done using the static type of the object
- The decision is made at compile time

  Circle circle;          //Derived class object
  Shape& rshape = circle; //Reference to base class, bound to a circle object
  rshape.draw();          //calls Shape::draw()

- This is known as "static binding"

--------------------------
Dynamic Binding
--------------------------
- However, there are some cases where the compiler does not make the decision
- Instead, it generates some code which is used to make the decision
- The program will use this code to decide, at run time, which function to call
- It will use the dynamic type of the object
- This is known as "dynamic binding"

------------------------------
Dynamic Binding Requirement
------------------------------
- Two conditions must apply for dynamic binding to occur
  * A member function is called through a pointer to reference to a base class
  * The member function was declared virtual in the base class

-----------------------------
The Virtual Keyword
-----------------------------
- To make a member function virtual, we put the virtual keyword before its
declaration in the base class
   virtual void draw(); //declare the member function as virtual in base class
- This virtual member function will be inherited in all sub-classes
  * We do not need to write "virtual" again
- A child class which reimplements a virtual function is said to "override" it

-------------------------------------
Virtual Member Function Call
-------------------------------------
class Shape{
  public:
    virtual void draw() const; //Base class defines virtual draw() member
                               //function
};

class Circle : public Shape{
  public:
    void draw() const; //child class overrides virtual draw() member function
};

Circle circle;           //Derived class object
Shape& rshape = circle;  //Reference to base class, bound to a Circle object
rshape.draw();           //Uses dynamic binding to call Circle::draw()

-------------------------------------
Function Call Argument
-------------------------------------
- Virtual functions solve the problem with function call arguments
- We pass a reference or pointer to the base class
- The version for the dynamic type of the object will be called

   //The static type of d is reference to const shape
   //The dynamic type of d is reference to const {some class in Shape hierarchy}
   void draw_shape(const Shape& d){
     d.draw(); //calls draw member functions of Circle etc
   }
*/

#include <iostream>

using namespace std;

class Shape {
public:
  virtual void draw() const { cout << "Drawing a generic shape...\n"; }
};

class Circle : public Shape {
public:
  void draw() const { cout << "Drawing a circle...\n"; }
};

class Triangle : public Shape {
public:
  void draw() const { cout << "Drawing a triangle...\n"; }
};

void draw_shape(const Shape &s) { // argument is a reference to a Shape
  s.draw();                       // calls draw member function of Circle etc
}

int main() {

  Circle circle;        // Derived class object
  draw_shape(circle);   // draw_shape will call Circle's version of draw()
  Triangle triangle;    // Derived class object triangle
  draw_shape(triangle); // draw_shape will call Triangle's version of draw()
}

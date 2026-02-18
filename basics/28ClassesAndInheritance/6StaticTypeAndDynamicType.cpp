/*
------------------------------
Static Type and Dynamic Type
------------------------------
- what is the type of pshape?

  class Shape{};
  class Circle : public Shape{};

  Circle circle;
  Shape* pshape = &circle;

- pshape is declared as a pointer to Shape
- pshape is the address of a Circle object
- So what actually is the type of pShape?
  * Is it a pointer to Shape, or pointer to Circle?
  * Correct answer is both! In C++, variables actually have two types: the
    static type and the dynamic type

------------------------
Static Type
------------------------
- The static type is the type used in the variable declaration

  int x{5};                  //Static type int
  int* px = &x;              //Static type pointer to int

  Circle circle;             //Static type Circle
  Circle *pcircle = &circle; //Static type pointer to Circle
  Circle& pcircle = circle;  //Static type reference to Circle

  Shape *pshape = &circle;   //Static type pointer to Shape
  Shape& rshape = circle;    //Static type reference to Shape

----------------------------
Dynamic Type
----------------------------
- The dynamic type is the type of the variable in memory
- For most objects, this will be the same as the static type

  int x{5};                   `//Dynamic type int
  int* px = &x;               //Dynamic type pointer to int

  *Circle circle;             //Dynamic type Circle
  Circle *pcircle = &circle;  //Dynamic type pointer to Circle
  Circle& pcircle = circle;   //Dynamic type reference to Circle

- However, it can be different for a pointer or reference to a base class

  Shape *pshape = &circle;    //Dynamic type pointer to Circle
  Shape& rshape = circle;     //Dynamic type reference to Circle

-------------------------------------
Static vs Dynamic Typing
-------------------------------------
- C++ almost always uses static typing
  * Type checking and function call resolution is done by the compiler
  * Less runtime overhead
  * Better optimization
- The dynamic type is only used for a pointer or reference to a base class
  * The compiler does not decide which member function to call
  * Instead, the member function is chosen at runtime, using the object in
    memory

-------------------------
Using the Dynamic Type
-------------------------
- To use the dynamic type, we declare the member function as "virtual" in the
base class
- When we call it through a pointer or reference to the base class, the dynamic
type of the object will be used

  Class Shape{
    public:
        virtual void draw(); /Declare Shape::draw() as virtual
    ...
  };

  Shape* pshape = new Circle();
  pshape->draw(); //Resolved at run time

- Now, when we call it through the pointer to Shape, the compiler will not get
to decide that this is a member function of Shape. Instead, the program will
decide that this is a Circle object. So this will call circle version of draw()
*/

#include <iostream>
#include <vector>

using namespace std;

class Shape {
public:
  virtual void draw() { cout << "Drawing a generic shape...\n"; }
};

class Circle : public Shape {
public:
  void draw() { cout << "Drawing a circle...\n"; }
};

int main() {
  vector<Shape *> shapes; // vector of pointers to shape objects

  // create a pointer to a child class of Shape and append it to the vector
  shapes.push_back(new Circle());

  for (auto shape : shapes) {
    shape->draw(); // calls Circle::draw()
  }

  for (auto shape : shapes) {
    delete shape;
  }

  // So the pointer to Shape has the static type of pointer to Shape, but the
  // dynamic type is pointer to Circle. And that called the Circle member
  // function
}

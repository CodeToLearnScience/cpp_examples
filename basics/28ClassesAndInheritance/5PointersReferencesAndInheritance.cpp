/*
--------------------------
Pointers and Inheritance
--------------------------
- Normally a pointer must point to a variable of the same type
- However, a pointer to a base class can point to any object in the same
hierarchy

  class Shape{};
  class Circle : public Shape{};

  Circle circle;           //derived class object
  Shape* pshape = &circle; //Pointer to base class, points to circle object

- However, we cannot go in the other direction

  Shape shape;               //Base class object
  Circle* pcircle = &shape;  //Error!

- This works because the way base and derived classes are stored in memory.
Circle object is part of shape

              Shape
           <---------->
           ........................
 pshape -> |           |           |
           ''''''''''''''''''''''''
           <----------------------->
                 Circle
- However, a Shape object may not necessarily be part of a Circle object
  * It could be a basic Shape object
  * Or part of some other derived class object

--------------------------
Member Function Calls
--------------------------
- We can call any public member function of Shape on pshape
  * This will call Shape's version of the function
- We cannot call any public member functions of Circle, even though the object
is "really" a Circle

   pshape->draw(); //call Shape's version of draw()
   pshape->area(); //Error! Not a member of Shape

- This is because the compiler sees pshape as pointing to a Shape object
- To do object-oriented programming, we need to be able to to use pshape as a
pointer to a Circle

*/
#include <iostream>
#include <vector>

using namespace std;

void pointer_and_ref_ex() {
  class Shape {};
  class Circle : public Shape {};

  Circle circle;          // derived class object
  Shape *shape = &circle; // pointer to base class, points to a Circle object

  // Shape shape;              //Base class object
  // Circle* pcircle = &shape; // Error!

  // Same way it works with references
  Shape &sref = circle;

  // Shape shape;
  // Circle& cref = shape;  // Error!
}

void pointer_and_ref_ex2() {

  class Shape {
  public:
    void draw() { cout << "Drawing a generic shape...\n"; }
  };

  class Circle : public Shape {
  public:
    void draw() { cout << "Drawing a circle...\n"; }
    void area() { cout << "Calculating area of circle...\n"; }
  };

  Circle circle;           // derived class object
  Shape *pshape = &circle; // pointer to base class, points to a Circle object

  // even though this pshape is actually representing a Circle object in memory
  // the compiler still thinks it is a Shape object. That's why it calls Shape
  // objects member functions
  pshape->draw(); // calls Shape's version of draw()
  // pshape->area(); //error as area is not a member of Shape
}

namespace member_function_call {
class Shape {
public:
  void draw() const { cout << "Drawing a generic shape...\n"; }
};

class Circle : public Shape {
public:
  void draw() const { cout << "Drawing a circle...\n"; }
};

void draw_shape(const Shape &s) {
  s.draw(); // Calls draw member function of Shape
}

void draw_shape(const Circle &c) {
  c.draw(); // Calls draw member function of a Circle
}

void example() {
  Circle circle;          // Derived class object
  Shape &rshape = circle; // Reference to base class, bound to a Circle object
  draw_shape(circle);
  draw_shape(rshape);
}

void example2() {
  vector<Shape *> shapes; // vector of pointers to Shape instances

  // create a pointer to child class of Shape and append it to the vector
  // Although we add a pointer to a Circle class when it goes into the container
  // but when it comes out of the container, it is now a pointer to the base
  // class (like in previous examples). So in a way we lost all the type
  // information when we add it to the container. One thing we could do is to
  // extend the Shape class, and add some kind of tag so we know what kind of
  // object it really represents. But that makes things rather complicated. Or
  // we could use a cast so when the pointer comes out of the container, we cast
  // it back to a pointer to Circle
  shapes.push_back(new Circle);

  for (auto s : shapes) {
    s->draw();                        // calls Shape::draw()
    static_cast<Circle *>(s)->draw(); // Now calls Circle::draw()
  }
  // However, the problem with cast is, if we add some different child class to
  // the container like
  //
  // shapes.push_back(new Triangle);
  //
  // Now we need to somehow know that we need to case the first element to
  // pointer to Circle. The second one to pointer to Triangle, and so on. That
  // is not a good solution. Fortunately we have solution and we will see that
  // next

  for (auto s : shapes) {
    delete s; // Release memory
  }
}
} // namespace member_function_call

int main() {

  pointer_and_ref_ex();
  pointer_and_ref_ex2();
  cout << "\n-----------member function call example---------\n";
  member_function_call::example();
  cout << "\n-----------member function call example2 with vector and "
          "new---------\n";
  member_function_call::example2();
}

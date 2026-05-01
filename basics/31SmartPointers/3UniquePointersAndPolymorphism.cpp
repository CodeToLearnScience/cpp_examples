/*
------------------------------------------
Unique Pointers and Polymorphism
------------------------------------------
------------------------
Polymorphism
------------------------
- Polymorphism is when we use a base class object to represent a derived class
object
- In C++, this requires using either a pointer or a reference

  vector<Shape*> shapes;
  shapes.push_back(new Circle);
  shpaes.push_back(new Triangle);
  shapes.push_back(new Square);

  for(auto& it : shapes){
    it->draw();
  }
- with "new Circle" we are going to get a pointer to a Circle object. We are
going to store this in the vector, as a pointer to a Shape object and then when
we iterate, we call the virtual draw() member function, and that will call the
draw() member function of the Circle. And the same fo the Triangle and Square.
Because we are using new, we have to manage the memory ourselves. So we have to
remember to release the memory.

----------------------------------------
Polymorphism with unique_ptr
----------------------------------------
- Now that we know about unique_ptr, we should use them wherever we can
- We can use unique_ptr instead of calling new() explicitly

  unique_ptr<Base> pbase{make_unique<Derived>()};

- When we call make_unique, we use the derived type as the parameter. So this
will allocate the memory for the child class. And it will return a unique_ptr
to the child class and then we move that into a unique_ptr to the base class. So
this "pbase" is a unique_ptr to a base class object, which is actually pointing
to a derived class object.
- The allocated memory will be manged by unique_ptr
  * pbase cannot be aliased
  * pbase cannot be accidentally released, overwritten or invalidated
  * Pointer arithmetic on pbase is now allowed
  * delete is called automatically on an exception
  * pbase cannot be accidentally be used after delete

----------------------------------------
The Factory Pattern
----------------------------------------
- Programmers often call a function to create a new object
- The function decides the type of the new object and returns a pointer to it
  * This is known as the "Factory pattern"
  * The type of the object will depend on the arguments to the function. That
    will say what kind of object to create, which child object
  * Useful when working with class hierarchies
  * Create a child class object and return it through a pointer to base

- Advantages of Factory pattern
  * All the code to create objects in the hierarchy is in a single place in the
    factory function
  * Flexibility - can use arguments to choose which child class type to create
    and you get polymorphic object back
  * Easy to extend if new child classes are added

-----------------------------------------
Factory Pattern with Traditional Pointers
-----------------------------------------
- Traditionally, the factory pattern was implemented with explicit pointers and
new/delete
  * Use new() to allocate an appropriate object and store a pointer to it
  * Return the pointer from the function
  * The caller has to delete the pointer after use

-----------------------------------------
Factory Pattern with unique_ptr
-----------------------------------------
- We can implement the factory pattern with a unique_ptr
  * Create an appropriate unique_ptr as a local variable
  * This will allocate the memory and store a pointer to it
  * Return the unique_ptr from the function
  * The unique_ptr will be moved into the function's return space
  * Then it will be moved into a variable in the caller
  * The caller's unique_ptr will automatically release the memory when it goes
    out of scope
*/

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

namespace polymorphism_ex {
class Shape {
public:
  virtual void draw() = 0;
  virtual ~Shape() = default;
};

class Circle : public Shape {
public:
  virtual void draw() override { cout << "Drawing a Circle...\n"; }
};

class Triangle : public Shape {
public:
  virtual void draw() override { cout << "Drawing a Triangle...\n"; }
};

class Square : public Shape {
public:
  virtual void draw() override { cout << "Drawing a Square...\n"; }
};

void example() {

  vector<Shape *> shapes;
  shapes.push_back(new Circle);
  shapes.push_back(new Triangle);
  shapes.push_back(new Square);

  for (auto &it : shapes) {
    it->draw();
  }

  for (auto &it : shapes) {
    delete it; // Memory leak if the pointers are not deleted
  }
}

void example_with_unique_ptr() {
  vector<unique_ptr<Shape>> shapes;
  shapes.push_back(make_unique<Circle>());
  shapes.push_back(make_unique<Triangle>());
  shapes.push_back(make_unique<Square>());

  for (auto &it : shapes) {
    it->draw();
  }
}
// when the function returns, the destructor for the vector will be called. This
// will call the destructor for the elements. With the pointer destructor, that
// does nothing, but with the unique_ptr destructor, that will release the
// memory

// Factory function
Shape *create_shape(int sides) {
  // The returned pointer will be copied into the function's return space
  if (sides == 1) // create 1-sided shape
    return new Circle;
  else if (sides == 3)
    return new Triangle; // create 3-sided shape
  else if (sides == 4)
    return new Square; // create 4-sided shape
  else
    cout << "Cannot create a shape with " << sides << "sides\n";
  return nullptr;
}

void old_factory_pattern_ex() {
  Shape *pshape = create_shape(3);
  if (pshape)
    pshape->draw();
  delete pshape; // memory leak if the pointer is not delete
}

// factory function with unique_ptr
unique_ptr<Shape> create_shape_with_unique_ptr(int sides) {
  // the returned unique_ptr will be moved into the function's return space
  if (sides == 1)
    return make_unique<Circle>();
  else if (sides == 3)
    return make_unique<Triangle>();
  else if (sides == 4)
    return make_unique<Square>();
  else
    cout << "Cannot create a shape with " << sides << "sides\n";
  return nullptr;
}

void unique_ptr_factory_pattern_ex() {
  // The returned unique_ptr will be moved into a variable in the caller
  auto pshape{create_shape(4)};
  if (pshape)
    pshape->draw();
  delete pshape; // memory leak if the pointer is not delete
}
} // namespace polymorphism_ex

int main() {

  polymorphism_ex::example();
  polymorphism_ex::example_with_unique_ptr();
  polymorphism_ex::old_factory_pattern_ex();
  polymorphism_ex::unique_ptr_factory_pattern_ex();
}

/*
------------------------------------------
Override and Overload of Virtual Functions
------------------------------------------
- A child class can define a member function with the same name as virtual
member functions in the parent class
- Override
  * Same signature as the parent
  * Circle and Triangle override the virtual draw() member function
- Overload
  * Different signature from the parent
  * Prevents dynamic binding
  * May hide the parent's member function
- It is easy to overload by mistake
  * Editing error when defining child function
  * Parent function's signature changes

---------------------------
The override Keyword
---------------------------
- C++11 introduced the "override" Keyword
- We can add this to the definition of a member function in a child class

   void draw() const override; //Child class overrides Shape::draw()

- The compiler will check whether this member function overrides a virtual
member function in the parent class
- The compiler will give an error if the function doesn't override

----------------------
The final Keyword
----------------------
- C++11 also introduced the "final" Keyword
  * A final class cannot be derived from
  * A final member function cannot be overridden in a child class
- Libraries often use "final"
  * The library can provide a class hierarchy, or use one internally
  * Users of the library cannot extend this class hierarchy
*/

#include <iostream>

using namespace std;

class Shape {
public:
  virtual void draw() const { cout << "Drawing a generic shape...\n"; }
};

class Circle : public Shape {
public:
  void draw() const override {
    cout << "Drawing a circle...\n";
  } // Ok - overrides Shape::draw()
  // void draw(int radius) const override; // Error! Does not override
  void draw(int radius) const; // Ok - overload
};

namespace demo_final_keyword_for_class {
class Shape {
public:
  virtual void draw() const;
};

class Circle final : public Shape {
public:
  void draw() const override;
};

class DeluxeCircle : public Circle { // Error overriding a class declared final
public:
  void draw() const override; // Error! overridding final function
};
} // namespace demo_final_keyword_for_class

namespace demo_final_keyword_for_virtual_func {
class Shape {
public:
  virtual void draw() const;
};

class Circle : Shape {
public:
  void draw() const override final;
};

class DeluxeCircle : public Circle {
public:
  void draw() const override; // Error! overridding final function
};
} // namespace demo_final_keyword_for_virtual_func

int main() {
  Circle circle;
  circle.draw();
}

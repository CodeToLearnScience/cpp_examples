/*
---------------------------------------
Run Time Type Information (RTTI)
---------------------------------------
- RTTI relates to the dynamic type of the object
  * typeid
  * type_info
  * dynamic_cast

----------------
typeid
----------------
- std::typeid() returns Information about the dynamic type of its argument
- Defined in <typeinfo>
- Mainly used in comparisons

    Circle d;
    Shape *pShape = &d;
    if(typeid(*pShape)==typeid(Circle)){
        cout << "pShape points to a Circle object\n";
    }
    else{
        cout << "pShape does not point to a Circle object\n";
    }

---------------
type_info
---------------
- std::type_info is a class defined in <typeinfo> //remember typeinfoy is
  different
    typeid() returns a type_info object
- It contains information about the dynamic type of an object

------------------------
type_info::name()
------------------------
- type_info::name() member function returns a C-style string
  * Unique for each type
  * The contents of the string are compiler-specific
  * Generally not useful

  cont type_info& tShape = typeif(*pShape);
  cout << "Dynamic types of pShape is" << tShape.name() << "\n";

-------------------------
type_info::hash_code()
-------------------------
- type_info also has a hash_code member function
- This returns a unique number for each dynamic type. Maybe you could use it for
doing something clever like writing your own hash tables or something like that

    const type_info& tShape = typeid(*pShape);
    const type_info& tCircle = typeid(Circle);

    if(tShape.hash_code()) == tCircle.hash_code())
        cout << "pShape points to a Circle object\n";
    else
        cout << "pShape does not point to a Circle object\n";

-------------------------
dynamic_cast
-------------------------
- dynamic_cast converts pointer to Base to a pointer to Derived
    * Also applies to references. So we can convert a references to base into a
    references to derived
- It allows us to check at runtime whether a Base-to-Derived conversion is
possible
- This only works if the dynamic type of the Base object is Derived
- If it fails, it returns nullptr
    * For references, it throws the std::bad_cast exception

----------------------------
Using dynamic_cast
----------------------------
- dynamic_cast is often misused to avoid writing virtual functions
- One legitimate use is for calling a member funtion that only exists in the
Ciecle class. Because if you try to call it through pointer to base, or
reference to base, the compiler will use the static type. And it will say that
function is not defined for the base class. So this is the only way to do it.

    Circle *pCircle = dynamic_cast<Circle*> (pShape);
    if(pCircle){
        cout << "Calling Circle_func()\n";
        pCircle->Circle_func();
    }
    else{
        cout << "Pshape does not point to a Circle object\n";
    }
- dynamic_cast is something that you should only use very rarely. Quite often
when people do use it, it is because they do not really understand how
inheritance works in C++. They think that you have to do dynamic_cast before
you can call a member function on the child class, and that is not correct.
What you should do is write virtual functions in the base class, then override
them in the child class. And then the compiler will do all the work for you.

*/

#include <exception>
#include <iostream>
#include <typeinfo>

using namespace std;

class Shape {
public:
  virtual ~Shape() = default;
};

class Circle : public Shape {};
class Triangle : public Shape {};

namespace dynamic_cast_ex {
class Shape {
public:
  virtual ~Shape() = default;
};

class Circle : public Shape {
public:
  void func() { cout << "Calling Circle's func()\n"; };
};

class Triangle : public Shape {};

void example() {

  Circle circle;
  Triangle triangle;
  // Shape *pShape = &circle;
  Shape *pShape = &triangle;

  Circle *pCircle = dynamic_cast<Circle *>(pShape);
  // pCircle may be nullptr. So checking before dereferencing
  if (pCircle) {
    pCircle->func();
  } else {
    cout << "Could not cast pShape to circle*\n";
  }
}

void using_dynamic_cast() {
  Circle circle;
  Triangle triangle;
  Shape &pShape = circle;
  // Shape &pShape = triangle;

  // pShape.func(); // if we try to use directly. It doesn't compile
  //  since dynamic_cast can throw exception, we need try and catch block
  try {
    // throw std::bad_cast on error
    Circle &pCircle = dynamic_cast<Circle &>(pShape);
    pCircle.func();
  } catch (std::exception &e) {
    cout << "Caught exception: " << e.what() << "\n";
  }
}

} // namespace dynamic_cast_ex

int main() {
  Circle circle;
  Triangle triangle;
  Shape *pShape = &circle;
  // Shape *pShape = &triangle;

  // Do *pShape and circle have the same dynamic type?
  if (typeid(*pShape) == typeid(circle)) {
    cout << "pShape points to a Circle object\n";
  } else {
    cout << "pShape does not point to a Circle object\n";
  }

  cout << "\n--------------Dynamic type of pShape is--------------------\n";
  const type_info &tShape = typeid(*pShape);
  const type_info &tCircle = typeid(circle);

  cout << "Dynamic type of pShape is " << tShape.name() << "\n";
  cout << "Dynamic type of circle is " << tCircle.name() << "\n";

  cout << "\n--------------Dynamic type of pShape is--------------------\n";
  cout << "Hash code of pShape is " << tShape.hash_code() << "\n";
  cout << "Hash code of circle is " << tCircle.hash_code() << "\n";

  if (tShape.hash_code() == tCircle.hash_code()) {
    cout << "pShape points to a Circle object\n";
  } else {
    cout << "pShape does not point to a Circle object\n";
  }
  cout << "\n--------------Dynamic Cast Example--------------------\n";
  dynamic_cast_ex::example();
  cout << "\n--------------Using Dynamic Cast--------------------\n";
  dynamic_cast_ex::using_dynamic_cast();
}

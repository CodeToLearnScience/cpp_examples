/*
----------------------
Polymorphism
----------------------
- Polymorphism comes from greek for "many forms". In programming, polymorphism
means that different types have the same interface
  * which means, they have the same behaviour
- STL containers are an example of polymorphism
  * vector<int> is a different type from vector<string>
  * They have the same interface, regardless of element type
- This is known as "parametric polymorphism", because the element type is a
parameter of the vector

----------------------------------
Polymorphism and Inheritance
----------------------------------
- The classes in an Inheritance hierarchy have the same interface
  * Shape, Circle, and Triangle all have draw() member function
- This is known as "subtype polymorphism"
- An object of type can be replaced by an object of its subtype. So anywhere
that uses a base class can also use a derived class
  * The Liskov substitution principle
  * One of the fundamental concepts in object-oriented programming

--------------------------------
Importance of Polymorphism
--------------------------------
- Polymorphism is a very useful programming technique
- When we have related types, we can write one set of code which handles all of
them
  * Avoids duplicated code
- We can add new types without having to write extra code to handle them
  * Saves programming time
- However, it still respects the individual properties of a particular type, so
when we pass a Triangle to draw_shape(), it draws a Triangle and not some other
object

----------------------------------
Subtype Polymorphism in C++
----------------------------------
- In C++, subtype polymorphism is implemented using pointers or references to
the base class and calling virtual functions on them

  vector<Shape *> shapes;
  ...
  for(auto shape: shapes)
    shape->draw(); //Uses dynamic binding to call Circle::draw(), etc

- This allows us to use the same code to handle different classes, but still
keeps type safety
  * The program will work out the correct way to draw each Shape in the
    container
  * Alternatively, each Shape in the container "knows" how to draw itself

------------------------
Polymorphism in C++
------------------------
- Subtype polymorphism
  * Run-time overhead (program has to decide which virtual function to call)
  * May require memory management
  * No control over child classes
  * Can result in large, unmaintainable Inheritance hierachies
- Parametric Polymorphism
  * Compile-time binding
  * No run-time overhead
  * No memory allocation
  * More control over which types are instantiated (SFINAE, C++20 concepts)

-------------------------
When to use Inheritance
-------------------------
- Inheritance is often over-used
- Often when people are trying to fix a bug or add a feature and they have a
tight deadline, they tend to grab a class that does something vaguely similar,
inherit from it and then use their derived class to fix all the things that they
do not like. That's not really the correct approach. If you just want to call
the class's interface, then you should make an object of that class a data
member, and then call the public member functions. So that is composition
- Many problems are better solved by composition. Because it reduces coupling
  * To use a class's interface, make it a data member
- The trend in C++ is away from subtype polymorphism towards paremetric
polymorphism
- Only use Inheritance if you need an "is-a" relationship
*/

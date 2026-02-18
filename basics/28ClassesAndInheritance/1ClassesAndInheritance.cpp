/*
----------------
Class Hierarchy
----------------
- Programmers often work with entities which are related or represent similar
concepts
  * Graphical Shapes all have position on the screen, can be drawn, filled,
    rotated, etc
  * Elements in a document (text, tables, diagrams) can be formatted, moved,
    zoomed, etc
  * C++ input streams process input from different sources and convert it to
    data
- A class hierarchy can
  * Express these relationships
  * Make it easier for related classes to reuse code

  Example
  Shape => Shape is a basic graphical entity
  {Circle, Square, Triangle}=> These are specialized graphical entities

--------------------------
Input Stream Hierarchy
--------------------------
istream -> istream is a basic input stream
"ifstream" and "istringstream" are specialized input streams

-------------------
Base Classes
-------------------
- The class at the top of the hierarchy represents the most general or the most
basic version
- This is known as the "base class"
  * Graphical shapes have "Shape" as thier base class
  * Input Streams have istream as thier base class

----------------------
Derived Classes
----------------------
- Classes below the base class are known as "derived classes" or "subclasses"
- They are said to "inherit from" or "derive from" the base class
- These re more specialized versions of the base class, or enhanced versions
with more features
- Shape has Circle, Triangle,... as derived classes
  * Specific kinds of Shape
- ifstream and istringstream derive from istream
  * specialized streams which interact with files and std::string objects

-----------------------------
Inheritance
-----------------------------
- The relationship between classes at different levels in the hierarchy is
called "Inheritance"
- Inheritance models an "is-a" or "is-a-kind-of" relationship between classes
  * An istringstream is a kind of istream
  * A Circle is a shape
*/

/*
-------------------------------
Classes and Templates
-------------------------------
- Template classes work very much like other classes
  * Friend functions and classes
  * Static members
  * Member functions with default arguments
  * etc
- Template classes can be part of inheritance hierarchies
  * Base class or derived class
- Template classes can be composed

-------------------------------------------
Templates and member functions
-------------------------------------------
- A templated member function of a class is called a "member template"
  * The class does not have to be templated to have a member template
  * A member template can have different parameters from the class
- A member template cannot be virtual

-------------------------------------------
Generic Lambda implementation
-------------------------------------------
- Generic lambda expressions are implemented as classes with a member template
  //The arguments of func can have any type
  //So long as the + operator is defined for them

   auto lambda = [](auto x, auto y) {return x + y};

   //implemented as
    class functor{
    public:
      template<typename T>
      T operator()(T x, T y) {return x +y}; //lamda expression
    };

    lambda(2, 5);  //implemented as functor()(2,5)

----------------------------------------------------------
Member template with different parameter
----------------------------------------------------------
- Although the parameters are different, there is in fact a coupling between
them
  * Func has to be a callable object which can compare two objects of type T.
    The members of the class have to be a type which is comparable. Thye have to
    support less than operator
  * If this is not the case, we will get a compiler error when the template is
    instantiated
- C++20 has concepts
- concepts allow us to express this requirement as part of the template
definition
  * Clearer code which expresses the programmers intentions
  * Compiler errors will clearly state why the code did not compile
*/

#include <iostream>

using namespace std;

// C++14 generic lambda
auto lambda = [](auto x, auto y) { return x + y; };

// equivalent functor class with member template
class functor {
public:
  template <typename T> T operator()(T x, T y) {
    return x + y;
  }; // lamda expression
};

// we can also have a member template which has different parameter from the
// class
template <typename T> class comparer {
  T t1, t2;

public:
  comparer(const T &t1, const T &t2) : t1(t1), t2(t2) {}

  // member template with parameter Func
  template <typename Func> bool compare(Func f) { return f(t1, t2); }
};

int main() {
  // create functor object, instantiate its function call operator and call it
  cout << "functor()(2, 5): ";
  cout << functor()(2, 5) << "\n";
  cout << "lambda()(2, 5): ";
  cout << lambda(2, 5) << "\n";

  std::cout << "\n-----------------------------------------------\n";
  int x{1}, y{2};

  // instantiate a comparer oject where T is an int
  comparer<int> c(x, y);
  cout << "comparer class: t1 = " << x << ", t2 = " << y << "\n";

  // instantiate comparer: compare() where Func is an lambda expression. A
  // callable argument. The compiler will deduce the type of "Func" from
  // argument that is going to be the same type as this lambda expression. The
  // functor that the compiler will generate. And then it will call this
  // function
  auto b = c.compare([](int i1, int i2) { return i1 < i2; });
  cout << "Result of calling compare: " << boolalpha << b << "\n";
}

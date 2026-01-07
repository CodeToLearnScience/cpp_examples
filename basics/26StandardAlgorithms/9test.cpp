/*
The compiler will create a class to implement the lambda expression, and an
object of that class. Since the lambda expression is mutable, the members of
this object can be modified.

x and y are captured by value. This means that the corresponding members of the
object are copies of x and y. If these members are modified, the x and y
variables will not be changed.

z is captured by reference. The corresponding member of the object will be a
reference to z. If this member is modified, the z variable will be modified as
well.

When the lambda expression is executed, the copies of x and y are incremented
and used to calculate the value of z.

After the first execution, the object's members will have the values 43, 100 and
143. The local variables will have the values 42, 99 and 143.

After the second execution, the object's members will have the values 44, 101
and 145. The local variables will have the values 42, 99 and 145.
*/

#include <iostream>

int main() {

  int x{42};
  int y{99};
  int z{0};

  auto lam = [=, &z]() mutable {
    ++x;
    ++y;
    z = x + y;
  };

  // because of mutable x and y will be modified but within scope of lambda
  // function so x will be 43 and y will be 100 and z will be 143 and similarly
  // in next call. But outside of the lambda function x and y will remain 42 and
  // 99
  lam();
  std::cout << x << " " << y << " " << z << "\n";

  lam();
  std::cout << x << " " << y << " " << z << "\n";
}

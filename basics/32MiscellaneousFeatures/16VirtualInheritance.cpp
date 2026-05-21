/*
------------------------------
Virtual Inheritance
------------------------------
- One of the problems which can arise in multiple Inheritance is if the parent
classes both inherit from the same base class
- In multiple Inheritance, it is possible for both the parents to have the same
base class


+---------------------------+
| Sales Employee            |
| and Manager both          |
| inherit from Employee     |
+---------------------------+


                +----------+               +----------+
                |          |               |          |
                | Employee |               | Employee |
                |          |               |          |
                +----------+               +----------+
                     |                          |
                     v                          v
                +-----------+             +---------+
                |   Sales   |             |         |
                |  Employee |             | Manager |
                |           |             |         |
                +-----------+             +---------+
                      \                       /
                       \                     /
                        v                   v
                            +-----------+
                            |   Sales   |    | Manager multiply inherits |
                            |  Manager  |    | from Sales Employee       |
                            |           |    | and Manager               |
                            +-----------+    +---------------------------+

---------------------------------------
Employee Hierarchy
---------------------------------------
- A SalesManager object will contain an SalesEmployee object and a Manager
object
- Each of these objects contains a separate Employee object
- This is not desirable
  * The SalesManager represents a unique Employee

------------------------------------
Virtual Inheritance
------------------------------------
- When we executed the code, we saw that Employee address was different which is
not what we wanted. So this can be solved by Virtual Inheritance
- So This can be solved by making SalesEmployee and Manager use "virtual"
inheritance from Inheritance

   class SalesEmployee: public virtual Employee{};
   class Manager: public virtual Employee{};

- This makes Employee a "virtual base" of SalesEmployee and Manager
- The SalesEmployee and Manager parts of a SalesManager object will now share a
single Employee object
- SalesManager is defined as usual
    class SalesManager: public SalesEmployee, public Manager{};

+------------------------------------+
| Sales Manager object               |
| contains only one Employee object  |
+------------------------------------+


                            +----------+
                            |          |
                            | Employee |
                            |          |
                           /+----------+ \
                          /               \
                         v                 v
                +-----------+             +---------+
                |   Sales   |             |         |
                |  Employee |             | Manager |
                |           |             |         |
                +-----------+             +---------+
                      \                       /
                       \                     /
                        v                   v
                            +-----------+
                            |   Sales   |    +---------------------------+
                            |  Manager  |    | SalesEmployee and Manager |
                            |           |    | both contain the same     |
                            +-----------+    | Employee object           |
                                             +---------------------------+

*/

#include <iostream>

using namespace std;

namespace without_virtual_inheritance {
class Employee {
public:
  void address() {
    cout << "Employee address = " << static_cast<void *>(this) << "\n";
  }
};

class SalesEmployee : public Employee {};
class Manager : public Employee {};
class SalesManager : public SalesEmployee, public Manager {};

void example() {
  SalesManager sm;

  cout << "Cast to SalesEmployee\n";
  // we are allowed to access those inner objects through pointers, so we can
  // take the address of the SalesManager, cast it to SalesEmployee, and that
  // will give us a pointer to the SalesEmployee part
  SalesEmployee *se{static_cast<SalesEmployee *>(&sm)};
  se->address();

  cout << "Cast to Manager\n";
  Manager *m{static_cast<Manager *>(&sm)};
  m->address();
  // when we execute, we can see different address
}

} // namespace without_virtual_inheritance

namespace with_virtual_inheritance {
class Employee {
public:
  void address() {
    cout << "Employee address = " << static_cast<void *>(this) << "\n";
  }
};

class SalesEmployee : public virtual Employee {};
class Manager : public virtual Employee {};
class SalesManager : public SalesEmployee, public Manager {};

void example() {
  SalesManager sm;

  cout << "Cast to SalesEmployee\n";
  // we are allowed to access those inner objects through pointers, so we can
  // take the address of the SalesManager, cast it to SalesEmployee, and that
  // will give us a pointer to the SalesEmployee part
  SalesEmployee *se{static_cast<SalesEmployee *>(&sm)};
  se->address();

  cout << "Cast to Manager\n";
  Manager *m{static_cast<Manager *>(&sm)};
  m->address();
  // when we execute, we can see different address
}

} // namespace with_virtual_inheritance

int main() {
  cout << "+------------without_virtual_inheritance-------------+\n";
  without_virtual_inheritance::example();
  cout << "+------------with_virtual_inheritance-------------+\n";
  with_virtual_inheritance::example();
}

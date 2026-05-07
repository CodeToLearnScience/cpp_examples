/*
------------------------
Duration units
------------------------
- <chrono> defines integer types which represent units of duration
  * These are in the std::chrono namespace
- These are used to measure time intervals
  * hours
  * minutes
  * milliseconds
  * microseconds
  * nanoseconds
- C++20 also has days, weeks, months and years

--------------------------
Duration Initialization
--------------------------
- Duration units are default-initialized
  seconds sec; //undefined value
- The constructor takes a single argument
  * hours hour{5};         //5 hour interval
  * minutes min{10};       //10 minute interval
  * seconds sec{2};        //2 second interval
  * milliseconds msec{20}; //20 milliseconds
  * microseconds usec{50}; //50 microseconds
  * nanoseconds nsec{80};  //80 nanoseconds

-------------------------
std::chrono literals
-------------------------
- C++14 provides literals for these units

  using namespace std::literals;

  * auto hour = 5h;         //5 hour interval
  * auto min = 10min;       //10 minute interval
  * auto sec = 2s;          //2 second interval
  * auto msec = 20ms;       //20 milliseconds
  * auto usec = 50us;       //50 microseconds
  * auto nsec = 80ns;       //80 nanoseconds

------------------------
count() member function
------------------------
- Duration types cannot be printed out directly
  cout << sec << endl; //Error
- The count() member function returns the numeric value of the duration
  cout << sec.count() << endl; //OK
- Should be used only for I/O and interfacing to legacy code

--------------------------
Implicit Conversion
--------------------------
- The constructor is explicit

   seconds sec = 2; //Error - cannot convert from int
   seconds sec = 2s; //OK

- The conversion operators are also explicit

   void func(seconds); //Function taking chrono::seconds argument
   func(2);            //Error-cannot convert from int
   func(2s);           //OK

--------------------------
Explicit Conversion
--------------------------
- Conversion between durations can be done Implicitly if there is no loss of
data
  seconds s = 1h;     //OK, s = 3600 seconds
  seconds s = 5043ms; //Error - data would be lost

- Use duration_cast for explicit conversion

  seconds s = duration_cast<seconds>(5043ms); //OK, s is truncated to 5 seconds
  seconds s = duration_cast<seconds>(-5043ms) //s is truncated to -5seconds
                                              //not -6. Truncated towards 0
*/

#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;
using namespace std::literals; // for suffixes

namespace chrono_ex {

void example() {
  seconds s; // undefined value

  cout << "Uninitialized seconds variable has value " << s.count() << "\n";

  auto hour = 5h;   // 5 hour interval
  auto min = 10min; // 10 minute interval
  auto sec = 2s;    // 2 second interval
  auto msec = 20ms; // 20 milliseconds
  auto usec = 50us; // 50 microseconds
  auto nsec = 80ns; // 80 nanoseconds

  cout << "hour = " << hour.count() << " hours " << "\n";
  cout << "mins = " << min.count() << " minutes " << "\n";
  cout << "sec = " << sec.count() << " seconds " << "\n";
  cout << "msec = " << msec.count() << " milliseconds " << "\n";
  cout << "usec = " << usec.count() << " nanoseconds " << "\n";
  cout << "nsec = " << nsec.count() << " nanoseconds " << "\n";
}

void chrono_ops() {
  seconds sec;
  auto s1 = 2s;
  auto s2 = 3s;
  cout << "s1 = " << s1.count() << " seconds\n";
  cout << "s2 = " << s2.count() << " seconds\n";

  sec = s1 + s2;
  cout << "sec = " << sec.count() << " seconds\n";

  auto msec = sec + 43ms;
  cout << "msec = " << msec.count() << "milliseconds\n";
}

void func(seconds sec) { // function taking chrono::seconds argument
  cout << sec.count() << " seconds\n";
}

void func_ex() {
  seconds sec = 2s;
  // func(2);  // Error
  func(3s); // OK
}

void conversions() {
  seconds sec1 = 1h;
  cout << "sec = " << sec1.count() << " seconds\n";

  // seconds = sec2 = 5043s; //Error - data would be lost

  seconds s = duration_cast<seconds>(5043ms); // OK - s is truncated to 5 sec
  cout << "5043ms converted to " << s.count() << " seconds\n";

  seconds s2 = duration_cast<seconds>(-5043ms); // OK - s is truncated to -5 sec
  cout << "-5043ms converted to " << s2.count() << " seconds\n";
}
} // namespace chrono_ex

int main() {
  chrono_ex::example();
  chrono_ex::chrono_ops();
  chrono_ex::func_ex();
  chrono_ex::conversions();
}

/*
------------------------------
Chrono Clocks and Time Points
------------------------------
---------
Clocks
---------
- The std::chrono library provides three clocks
- system_clock
  * Measures "wall time" using the hardware system's clock
- steady_clock
  * Idealized clock which only goes forwards, one tick at a time
- high_resolution_clock
  * Clock with the shortest tick period supported by the system
  * Implementation-defined. Usually an alias for system_clock or steady_clock
  * In practice its not very useful

-----------------------
System Clock
-----------------------
- The system clock is similar to the C library clock
  * Measures "wall time" using the operating system's clock
- It is the best clock for interactive use
  * Its time points relate to calenders, watches, phones etc.
  * Matches the user's view of time
- System clock is not well suited for measuring time intervals
  * The clock may be corrected if it runs fast or slow
  * Occasional adjustments for daylight saving, leap seconds
  * Changes may cause the clock to jump erratically or even go backwards

------------------
Steady Clock
------------------
- So the best clock for measuring time intervals is the steady_clock
- The steady clock is an Idealized clock
  * It only goes forwards, one tick a time ("monotonic"). So this is a bit like
    the program having its own internal stopwatch, and this will tick away
    constantly regardless of what time is doing in the outside world
- This is the best clock for measuring time intervals
  * External events can never cause the clock to jump around

-----------------------
Clock now() Function
-----------------------
- All three clock types have a static function now()
- This returns the clock's current time point

  system_clock::now()   //hardware clock
  steady_clock::now()  //steady clock

------------------------
Time point
------------------------
- The time_point class represents a point in time
- This contains a duration representing the time interval since the clock's
  "epoch"
  * A time_point object is associated with a particular clock
  * Calling the clock's now() function will return a time_point object
- Two time_point objects can be sutracted
  * The result will be a duration
- We can also add or subtract a time_point and a duration, giving a new
time_point

---------------------------
sleep_for() C++11
---------------------------
- The thread library provides a function which makes the current thread pause
or sleep for a specified duration

  #include <thread>
  cout << "Waiter! \n";
  this_thread::sleep_for(2s);
  cout << "You called, sir?\n";

- In a single-threaded program, this will make the main thread sleep for 2
seconds
- The actual duration maybe longer
  * Depends on scheduling
*/

#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono;

namespace sleep_for_ex {
void example() {
  std::cout << "Waiter! \n";
  std::this_thread::sleep_for(2s);
  std::cout << "You called, sir?\n";
}

} // namespace sleep_for_ex

long long fibonacci(long long n) {
  return (n < 2) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
  auto start = steady_clock::now(); // best one to use for measuring intervals
  long long n = fibonacci(45);
  std::cout << "Fibonacci number is " << n << "\n";
  auto finish = steady_clock::now();

  auto elapsed = duration_cast<milliseconds>(finish - start).count();
  std::cout << "Time taken: " << elapsed << " milliseconds\n";
  sleep_for_ex::example();
}

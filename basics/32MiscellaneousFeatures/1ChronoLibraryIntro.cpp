/*
------------------------------
Time and Dates in C++
------------------------------
- C++ inherited some time-handling types and functions from C
  * These are defined in <ctime>
  * Low-level and poorly desinged
- C++11 added the chrono library for time-handling
  * More precise, but involves complicated syntax
- C++20 extends the chrono library to handle dates
  * We will not look at it here

---------------------------------
Time in Traditional C++
---------------------------------
- clock() returns the number of "clock ticks" since the program started
  * These are stored in a variable of type clock_t (just a synonym for integer)
  * Can be used for intervals of up to a few seconds
  * Precision is implementation-defined (usually 1 microsecond)
  * You don't get number of seconds directly. You have to devide by a constant
    to get that

- time() takes a variable of type time_t (again synonym for integer) by address
  * It sets this argument to the number of seconds since 1st Jan 1970 midnight
  * Can be used for longer intervals (up to several decades)
  * Precision is 1 second

----------------------
std::chrono library
----------------------
- C++11 provided a new library to manage times
- Defined in <chrono>, in the std::chrono namespace (its own namespace under
  std)
- Three important concepts
  * Clock
    - Start date (epoch) and tick rate
    - C's clock started on 1 Jan 1970 (thats the epoch) and ticks once per
second
  * Time point
    - The number of clock ticks since the epoch, at a given point in time. That
      corresponds to the return value from calling the time() function in C.
  * Duration
    - An interval between two time points, measured in clock ticks. That's
      equivalent to calling the C function time() twice and subtracting  the
      return values.
*/

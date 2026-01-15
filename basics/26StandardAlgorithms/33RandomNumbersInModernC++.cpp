/*---------------------------------------
 Random Numbers in Modern C++
---------------------------------------
- C++11 introduced a number of classes for working with random numbers
- These are defined in <random>
  * Use a random number engine to generate the numbers
  * Use a distribution type to rescale the range
  * (Optional) use a random device to seed the engine

  Random device  --> seed --> Random Number engine --> Random number --> Random
number between m and n

- A random number engine is implemented as a functor
  * The constructor generates the sequence of pseudo-random numbers
  * When we call the () operator, we get the next number from the sequence

        default_random_engine end; //create engine object - generates sequence

        for(int i=0; i<5; i++){
          cout << eng() << ", "; //call the functor to get the next number
        }
 ---------------------
 Distribution
 ---------------------
 - A distribution is also implemented as a functor
    * Its constructor takes the range as arguments
    * Its overloaded () operator takes a function object as argument
    * This function object returns a number each time it is called
    * The distribution will then rescale this number to fit in the range and
return it
- A distribution can be used with any numerical data sequence, not just random
numbers
  * Very useful in stastical applications

-------------------------
Random Number Engines
-------------------------
- The two main random number engines are
- default_random_engine
  * implementation-defined
  * May be a wrapper around the rand() implementation
- mt19937
  * "Mersenne Twister" with period of 2^19937-1
  * Very fast at generating random numbers
  * Almost crypto secure (very hard to guess next number)
  * Has a lot of state (slow to initialize)
  * Usually the best choice for most requirements

---------------------
Distribution types
---------------------
- A distribution type fits its input into a statistical distribution
- The C++ library provides a number of distributions
  * Bernoulli, Normal, Poisson, etc.
- We usually want our random numbers to be uniformly distributed
  * All values in the range are equally probable
- uniform_int_distribution<T>(m,n)
  * Produces uniformly distributed integers of type T with values between m and
  n inclusive
- unifor_real_distribution<T>(m,n)
  * The same, but for floating-point numbers

-------------
random_device
-------------
- random_device produces a hardware-generated random number from system entropy
data
- However, it will produce a pseudo-random number if
  * The system does not provide entropy data
  * The compiler in GNU C++, which does not support entropy data
- If all the entropy data has been used up, it will stop and wait until more
data becomes available
- random_device is much slower than mt19937 but it is crypto secure if fully
implemented

---------------------
Using random_device
---------------------
- random_device is also implemented as a functor
  random_device rd; //random device (or maybe not!)

  for(itn i=0; i<5; ++i){
    cout << rd() << ", "; //get next number from random device
  }
- Because of the performance limitations, random_device is not suitable for
generating numbers in large quantities
- Instead, random_device is often used to generate a seed
  mt19937 mt(rd()); //seed the engine with a number from random_device

----------------------
Recommendations
----------------------
- Use mt19937 as your random number engine unless you have a particular need to
use one of the others
- Check the documentation before using random_device
- Make engine and distribution object static
  * Creating them is fairly time-consuming
  * Every time an engine is initialized, the sequence starts again
  * Usually you will only need one object per program anyway

-------------------
Health Warning
-------------------
- Random numbers, like floating-point numbers, contain a number of hidden
subtleties
- The material covered in this course is good enough for general purpose
applications
- If you are doing specialist work, you will need to have an in-depth
understanding of the topic
- This requires knowledge which is beyond the scope of this course
*/

#include <iostream>
#include <random>

using namespace std;

int main() {

  default_random_engine eng; // create engine object - generates sequence

  for (int i = 0; i < 5; i++) {
    cout << eng() << ", "; // call the functor to get the next number
  }
  cout << "\n";

  mt19937 mt; // Create engine object - generates sequence

  // we want ints in the range 0 to 10
  uniform_int_distribution<int> idist(0, 10);

  cout << "Five random integers between 0 and 10:\n";
  for (int i = 0; i < 5; ++i) {
    cout << idist(mt) << ", "; // call the functor to get the next number
  }
  cout << "\n";

  // we want flots in the range 0 to 10 /
  uniform_real_distribution<double> fdist(0, 10);

  cout << "Five random floating-point numbers between 0 and 10:\n";
  for (int i = 0; i < 5; ++i) {
    cout << fdist(mt) << ", "; // call the functor to get the next number
  }
  cout << "\n";
}

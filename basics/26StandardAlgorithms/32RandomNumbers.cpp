/* ------------------------
 Random Numbers
------------------------
- A random number is a number that appears to be chosen by chance
- Usually we assume that any number is equally likely to be chosen (unifrm
distribution)
- Usually we assume that next choice of number will not be affected by the
current choice (independednt)

--------------------------------
Applications of Random Numbers
--------------------------------
- Games (chance and uncertainity)
  * What hand is the player dealt?
  * Which way will opponent move?
- Simulation (Mote Carlo)
- Cryptography (unbreakable codes)
- Authentication
  * Security
  * Bitcoins and blockchains

--------------------------------
Software-derived Random Numbers
--------------------------------
- Software is deterministic so it cannot produce true random numbers
- However, there are "pseudo-random" number generators (PRNG)
- These are computational algorithms which generate a random looking sequence of
numbers

-------------------------
Seeding a PRNG
-------------------------
- To initialize a PRNG we use a number called a "seed"
  * The random number generator will produce a sequence of numbers based on this
seed
  * Each seed value produces a distinct sequence
- Using the same seed each time will produce the same sequence
  * This is useful for testing

-------------------------------------
Hardware-derived Random Numbers
-------------------------------------
- True random number generators (TRNG)
- Traditional: rolling dice, tossing coins etc
- Tables of data from measuring a physical process which produces random results
  * Thermal noise, radioactive decay
- Data available to sytem at runtime ("entropy")
  * Process ID, keyboard/mouse activity, temperature fluctuations
- Specialized hardware devices which generate data in real time

---------------------------------
Random Numbers in Older C++
---------------------------------
------
rand()
------
- rand() is inherited from C and is declared in <cstdlib>
- calling rand() returns the next number in sequence of pseudo-random numbers
- It returns an integer between 0 and RAND_MAX inclusive
- RAND_MAX is chosen by the implementation and there is no standard
  //print out a pseudo-random integer
   cout << rand() << endl;

---------------
rand() examples
---------------
- With a little arithmetic, we can get numbers within a different range of
values
  //print out a pseudo-random floating point number with values between 0 and 1
  cout << 1.0*ran()/RAND_MAX << "\n"; //convert the result to double

  //print out 10 pseudo-random integers with values between 1 and 100
  for(int i=0; i<100; i++){
    cout << (99*rand()/RAND_MAX+1) << endl;
  }

-----------------------
Seeding a PRNG
-----------------------
- To seed the generator used by rand(), we call srand()
- Traditionally, programmers use the current time to provide a "random" seed
  //time() is a C function, defined in <ctime>
  //srand(time(0)); //time(0) returns the current time
- The value returned by time() only changes once per second
- This makes it easier to guess the seed, which makes it easier to guess the
random sequence

------------------------
Disadvantages of rand()
------------------------
- The PRNG algorithm is chosen by the implementer
- Typical rand() implementations generate numbers which are not very random,
especially in the last few digits
- If we don't want to get numbers between 0 and RAND_MAX. we must rescale the
range. This introduces bias
  * Some numbers appear more often than others
- rand() has poor cryptographic security
  * The sequence is short and repeats frequently
  * Guessing the next number is not difficult enough
*/

#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

int main() {

  srand(time(0)); // use the current time as seed
  // print out a pseudo-random integer
  cout << "Printing out a random number... ";
  cout << rand() << "\n";

  // print out a pseudo-random floating point number with values between 0 and 1
  cout << 1.0 * rand() / RAND_MAX << "\n"; // convert the result to double

  // print out 10 pseudo-random integers with values between 1 and 100
  for (int i = 0; i < 10; ++i) {
    cout << (99 * rand() / RAND_MAX + 1) << endl;
  }
}

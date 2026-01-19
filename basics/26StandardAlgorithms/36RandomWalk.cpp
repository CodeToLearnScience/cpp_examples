/*-----------------------
 Random Walk practical
-----------------------
- Random walk occurs when a moving physical object changes direction at random
  * Also known as "drunkard's walk"
  * Brownian motion in Physics
- Describes many natural processes
  * Flight path of insects
  * Movement of molecules in a gas
  * Financial markets?
    - For long time it was thought that Financial markets follow random walk,
      but that's not quite true
- Used in games to characters move unpredictably

-------------------
character on Screen
--------------------
- x and y give the character's current position on the screen

        |
        |
      y |    (x,y) *
      | |
      v |_______________
              x->

- We are using the normal computer graphics convection, in which y=0 at the top
of the screen and increases as we go downwards. As opposed to the bitmap format
which is other way around
- If we want the character to be at some other position, we need to find out how
many pixels across, left or right, the character needs to move, and how many
pixels up or down, to get to the new position.

- To "move" the character
 * calculate its new position
 * Update the screen to display it again

     (x,y) --> (x+vx, y+vy)
  * vx pixels right and vy pixels down
  * we can have a loop. And on each iteration, the character moves to a new
position. We clear the screen and then we draw the screeen again, showing the
character in the new position
- Based on sign of vx, vy, the position of the character to the left or right is
decided
- To calculate the new position, we add the horizontal velocity vx to x and the
vertical velocity vy to y
 x+=vx; //update horizontal position
 y+=vy; //update vertical position
- If vx and vy do not change, the character will move in a straight line

----------------------------
Characters Moving at Random
----------------------------
- We can make this more interesting by making the character change direction at
random
  mt19937 mt;
  bernoulli_distribution bd; //50% chance of changing direction

  vx = bd(mt)?:vx:-vy; //if false, reverse horizontal motion
  vy = bd(mt)?:vy:-vy; //if false, reverse vertical direction
  x+=vx;               //update horizontal position
  y+=vy;               //update vertical position
- The character's path will follow a random walk
*/

// sample implementation without graphics library
#include <iostream>
#include <random>
#include <thread>

using namespace std;

int main() {
  int x{0};
  int vx{0};

  const int width{40};
  string blank_line(width, ' ');

  mt19937 mt;
  // we can introduce bias to the distribution by specifying value to
  // constructor
  // with 0.8 it means, we will get true 8 times out of 10 times
  bernoulli_distribution bd(0.8);

  while (true) {
    if (bd(mt)) {
      vx = 1;
      if (x == width) {
        vx = -1;
      }
    } else {
      vx = -1;
      if (x == 0) {
        vx = 1;
      }
    }
    x += vx;
    cout << "\r" << blank_line; //\r is carriage return character. So it means
                                // that anything that appears after that is
                                // going to be on same line, but at the start
                                // of the line
    string position(x, ' ');
    cout << "\r" << position << "." << flush;
    this_thread::sleep_for(100ms);
  }
}

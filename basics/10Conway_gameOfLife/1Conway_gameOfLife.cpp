/*complete implementation of cellular automata required infinite grid, so 
to restrict the grid size, we will have borders which are always unpopulated. 
If any cell on the border becomes populated, it will be ignored

- 2D array to represent grid 
- Elements of array will be "Cell" class 
- Game will be played in 80x24 terminal in text mode as there is no std 
graphics lib on C++
- We will use ANSI escape codes to display the cells on the terminal 

ANSI escape codes: 
- Before everyone had PC, people used so called dumb-terminals. This was 
keyboard and television like screen
- So you type something on the keyboard and it would go to a central computer 
and the central computer would send something back, which was displayed on the 
dumb-terminals
- There were various commands for changing the way the output appears 
- ANSI defined set of commands for controlling terminals 
- Programs can use these commands to change the way output is displayed 
- These begin with the "escape" character followed by a square bracket 0x1b[ 
- You can use different colored text, make it bold, italic, and so on
- Here we are interested in making text appear at certain positions on the 
screen 
- ex, move the cursor to rwo n, column m and display a character 
  ox1b[n;mH
- clear the screen and return the cursor to home 
  0x1b[2J

  PROGRAM LOGIC 
  - two grids one represents the current generation and the other next 
  generation
  - And then we are going to calculate if the cells in the current generation 
  will survice or be populated in the next generation 
  - so we start off by creating grid object, to represent the initial generation 
  - We populate the cells in that initial grid at random. Then we display it. 
  - Then we create a second grid object, which will represent the next 
  generation 
  - And then we calculate which cells will survive from this generation to 
  next generation and which ones will be newly populated 
  - Then we copy this grid over the current generation grid so next generation 
  grid becomes current generation and the first generation is suspended 
  - Repeat 
*/



#include <stdio.h>
#include <iostream>
#include <random> 


int main()
{

  int grid[23][79];

  std::mt19937 rng(std::random_device{}());
  std::uniform_int_distribution<int> d(0,4); //~20 live 
  for (int i=0; i<23; ++i){
    for (int j=0; j<79; ++j){
      grid[i][j] = (d(rng)==0) ? 1 : 0; 
    }
  }
  
  std::cout << "\x1b[H\x1b[2J";
  for (int i=0; i<23; ++i){
    for (int j=0; j<79; ++j){
      if(grid[i][j]){
        std::cout << "\x1b[32m" << "+" << "\x1b[0m";
      }
      else{
        std::cout << " ";
      }
    }
    std::cout << "\n";
  }
  std::cout << std::flush;
  return 0;
}

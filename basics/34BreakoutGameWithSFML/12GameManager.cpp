/*
-----------------
Game Manager
-----------------
- We need to refactor the code
  * main() is too long
  * Duplicated code
- We start by moving the code from main() into a new class

-------------------
game class
-------------------
- Data members
  * Game window
  * The ball
  * The background
  * The paddle
  * The vector of bricks

- Member functions
  * Constructor to initialize entities
  * run() to perform the game loop
  * reset() to re-initialize the entities

-------------------------
Pausing the game
-------------------------
- We will add a feature to allow the user to pause the game
  * While the game is paused, the entities are still redrawn
  * However, they are not updated
- We also allow the user to restart the game
- We add a class enum member to store the game state
  enum class game_state { paused, running };
*/

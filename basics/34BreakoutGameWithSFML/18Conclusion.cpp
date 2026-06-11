/*
-----------------
 Conclusion
-----------------
- We have implemented the game in 670 lines of code
  * Modular
  * Easy to understand (except for the entity_manager)
- Adding a new entity type to the game is straightforward
  * Derive a class from entity or moving_entity
  * Load its image file in the constructor
  * Override update()
  * Add data members and member functions
  * Create and register objects in game_manager::reset()
  * Add collision handling code to game loop if required

---------------------------
# Room for Improvement?
---------------------------
- Code refactoring
- Fix some minor ball/paddle interaction issues
- Add levels with faster ball, tougher bricks etc
- Make damaged bricks appear cracked
  * Draw lines on the rectangle
- Randomize brick strengths, reflection angles etc to add variety
- Add sound effects!

------------------
# Game Development
------------------
- This code is good for
  * Implementing simple games
  * Prototyping
- Not suitable for complex, performance-critical games
  * Vector reallocation
  * Virtual function calls
  * Run-time type information
  * Inheritance trees can become complex
  * Poor cache locality when iterating
- Entity Component System Architecture (ECS)
  * Used in game frameworks
*/

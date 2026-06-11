/*
------
Ball
------
- We will add the ball to our game
- Implement as a sprite which can move between updates

------------------
moving_entity
------------------
- Our game will have several sprites which can move
- We will add a moving_entity class to represent them
  * Subclass of entity
  * Represents an entity which can move on the screen
  * Has an sf::Vector2f member which represents the velocity of the entity
  * Abstract base class which inherits entity's pure virtual functions

------------------
Class Hierarchy
------------------
   entity
   /     \
  /       \
background \
            \
        moving_entity
             |
            ball

*/

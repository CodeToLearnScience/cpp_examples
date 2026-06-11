/*
------------------
Brick Strength
------------------
- When the ball hits a brick, the brick is destroyed immediately
- We will change the behaviour
  * The brick changes colour
  * The brick is "weakened"
  * It requires several impacts before the brick is finally destroyed
- We will add a "strength" member to the brick class
- Each time a ball hits the brick, its strength is decremented
- If the strength is equal to zero, the brick is destroyed

------------------
sf::Color
------------------
- SFML allows us to define our own colours
- sf::Color has four components
  * red
  * green
  * blue
  * alpha
- The components are 8-bit unsigned integers
- They define the contribution each component makes to the result
  * 0 represents "none"
  * 255 represents "full"
  * sf::Color(255, 0, 0) => red
- Alpha represents the opacity of the colour
  * 0 represents a completely transparent colour
  * 255 represents a completely opaque colour
  * By default, alpha is 255

--------------------
Implementation
--------------------
- In handle_collision(ball&, brick&)
  * Weaken the brick
  * Only destroy the brick if its strength is equal to 0
- In brick::update()
  * Set the colour of the brick, depending on its strength
*/

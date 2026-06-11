/*
----------------------
Random Walk
----------------------
- sf::Vector2
  * Represents a 2-dimensional vector
  * Members x and y can be accessed directly
  * Supports arithmetic operations, also == and !=
  * Template class
- sf::Vector2f
  * Alias for sf::Vector2<float> instantiation
  * SFML uses float internally

----------------------
Texture
----------------------
- sf::Texture represents an image
  * The image has been loaded into the graphics card
  * It can be drawn on a render target
  * The drawing is done inside the graphics card

----------------------
sf::Shape
----------------------
- sf::Shape represents a pre-defined texture
  * It can be drawn on a render target
  * Has an associated "texture rectangle"
  * All transformations are relative to the "origin" of the Shape
  * By default, this is the top left-hand corner of the texture rectangle

----------------------
sf::CircleShape
----------------------
- sf::Shape is an abstract base class
- sf::CircleShape is a subclass of sf::Shape
  * Also ConvexShape and RectangleShape
*/

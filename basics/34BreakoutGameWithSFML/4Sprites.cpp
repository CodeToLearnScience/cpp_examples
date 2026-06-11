/*
---------------
Sprite
---------------
- sf::Sprite represents a texture associated with a rectangle
  * Similar to sf::Shape, but we provide our own image
- Represents a group of pixels as a single graphical entity
- This entity "floats" over the display like a ghost

------------------
Creating a Sprite
------------------
- Use loadFromFile to load a texture into the graphics card
  sf::Texture texture;
  texture.loadFromFile("background.jpg");
- This will fail if
  * The image file is not valid
  * The image file is not in the expected directory
- Use setTexture to associate this texture with a sprite
  sf::Sprite sprite;
  sprite.setTexture(texture);

---------------
  entity class
---------------
- Our game will require several sprites
- We will create an "entity" class to represent them
- This will be an abstract base class
- The concrete sprite classes will inherit from entity
*/

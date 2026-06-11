/*
----------------
More Features
----------------
- We will add some more features to the game
  * Player "lives"
  * Text messages to communicate with the player

----------------
Text in SFML
----------------
- sf::Text represents graphical text
  * Can be drawn on a render target
- It has an associated sf::Font object
  * Controls the appearance of the text

----------------
 Creating Text
----------------
- Use loadFromFile to load a font
    sf::Font verdana;
    verdana.loadFromFile("/path/to/fonts/verdana.ttf");
- This will fail if
  * The font is not available on the system
  * The font file is not in the expected directory
- Use setFont to associate the font with a Text object
   sf::Text text;
   text.setFont(verdana);
   text.setString("hello");

---------------
 game_manager
---------------
- We will add a member for the number of "lives" the player has
  * Each time the ball hits the bottom of the screen, the player loses a "life"
  * When the player has no lives left, the game is over
  * If the player survives long enough to destroy all the bricks, they win the
game
- We add some more values to the game state
  * enum class game_state { paused, game_over, running, player_wins };
- We add text objects to display messages
*/

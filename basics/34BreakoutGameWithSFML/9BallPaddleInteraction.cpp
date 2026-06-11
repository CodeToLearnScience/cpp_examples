/*
------------------------
Ball-Paddle Interaction
------------------------
- We need to detect and resolve collisions between entities
- void handle_collision(ball &b, const paddle& p);
  * Makes the ball bounce off the paddle
  * An overload will make the ball destroy a brick
- bool is_interacting(const entity& e1, const entity& e2);
  * Returns true if e1's bounding box overlaps with e2's
- These will be non-member functions

---------------------
moving_entity class
---------------------
- We also add some helper functions to moving_entity
- These are needed because handle_collision() is a non-member function
  virtual void move_up() noexcept = 0;
  virtual void move_left() noexcept = 0;
  virtual void move_right() noexcept = 0;
*/

/*
----------------------------------
Ball Interaction with Bricks
----------------------------------
- When the ball hits a brick, the brick is destroyed
  * The ball bounces off the brick
- The brick disappears
  * The brick is deleted from the vector


----------------------------------
entity hierarchy
----------------------------------
- Add move_down() member function to moving_entity
- Add a member to store the destroyed state
- Add getter and setter for the destroyed member
- Add functions to get the edges of the sprite

---------------------
handle_collision()
---------------------
- Overload to handle collision of the ball with a brick
- The collision can occur on all four sides
- We also need to consider the ball's direction of travel

------------------
Overlaps
------------------
- left overlap = ball right - brick left
- right overlap = brick right - ball left
- top overlap = ball bottom - brick top
- bottom overlap = brick bottom - ball top

--------------------------
Side determination
--------------------------
- left overlap < right overlap == collision on left
- right overlap < left overlap == collision on right
- top overlap < bottom overlap == collision on top
- bottom overlap < top overlap == collision on bottom

--------------------
Ambiguity Resolution
--------------------
- Closer to left than top/bottom == ball goes to left
- Closer to right than top/bottom == ball goes to right
- Closer to top than left/right == ball goes up
- Closer to bottom than left/right == ball goes down
*/

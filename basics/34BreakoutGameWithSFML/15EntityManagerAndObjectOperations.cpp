/*
----------------------------
 entity_manager::get_all()
----------------------------
- get_all() returns all the entities of a given type
  * get_all<brick>(); // Returns all the bricks
- Find the hash code of the entity type
- Look up the hash code in the grouped_entities map
- Return the corresponding vector of aliases

-------------------------
 Collision Management
-------------------------
- Before:
    handle_collision(the_ball, the_paddle);

    for (auto& b: bricks) {
      handle_collision(the_ball, b);
    }

- We no longer have direct access to the entity objects

----------------------------
 Collision Management
----------------------------
- We could write code like this

  auto& balls = manager.get_all<ball>();        // Vector of ball objects
  for (auto& pball : balls) {                   // Create one ball object
    auto the_ball = dynamic_cast<ball*>(pball); // Cast entity* to ball*
    auto& bricks = manager.get_all<brick>();    // Vector of brick objects
    for (auto& pbrick : bricks) {
      auto the_brick = dynamic_cast<brick*>(pbrick); // Cast entity* to brick*
      handle_collision(*the_ball, *the_brick);    // Dereference the pointers
    }
  }
- This complicates the game loop

----------------------------
 entity_manager::apply_all()
----------------------------
- apply_all() applies a function to all the entities of a given type
    // Update all the bricks
    apply_all<brick>([](brick& b) {
      b.update();
    });

----------------------------
entity_manager::apply_all()
----------------------------
- Call get_all() to obtain the vector of aliases for the type
- Iterate over the vector of pointers to base class
- Cast each element to its dynamic type
- Call the function with the element as argument

----------------------------
Collision Management
----------------------------
// For every ball, call a function which
// For every brick, call a function
// Calls handle_collision with the ball and the brick as arguments

manager.apply_all<ball>([this](auto& the_ball) {
  manager.apply_all<brick>([&the_ball](auto& the_brick) {
    handle_collision(the_ball, the_brick);
  });
});

------------------
Code Organization
------------------
- The game_manager calls instantiations of these member templates
- We will write these inline in game.h, above the game_manager definition
*/

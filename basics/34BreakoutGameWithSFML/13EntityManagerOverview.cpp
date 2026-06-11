/*
--------------------
Entity Manager
--------------------
- We will refactor the entity management into a separate class
  * Simplify the game loop
  * Provide better abstraction

                          .........
    |-----------|    ---> | Create |
    | Game loop |    ---> | Update |
    |-----------|    ---> | Draw   |

     Game Manager      Entity Manager

-----------------
entity_manager
-----------------
- The entity manager will use polymorphism
  * Store entities as pointers to base class
  * Call virtual functions through pointer to base
- It will provide an interface for performing operations on entities
  * Operations on all entities in the game
  * Operations on all entities of a given type
- The entity_manager class will create all the entities in the game
- The manager will scan through all the entities on each update
  * It will delete any entities which have been destroyed in the game

----------------------------------
 entity_manager Class Data Members
----------------------------------
- all_entities
  * Stores all the entities in the game as a std::vector of
std::unique_ptr<entity>
- grouped_entities
  * Stores all the entities in the game as a std::map
  * The key depends on the entity type
  * The value is a std::vector of entity* with the same type
  * These pointers are aliases to the entity objects

-------------------------
Entity pointers
-------------------------

       -------------------------
            all_entities
       -------------------------
           |               |
        ball object     brick object
           |               |
     ---------------    ----------------
grouped_entities[ball]      grouped_entities[brick]

---------------------------------------------
 entity_manager Class Member Functions
---------------------------------------------
- create()
  * Create an entity object
  * Add it to all_entities and group_entities

- refresh()
  * Re-draw all the entities

- clear()
  * Destroy all the entities

- get_all()
  * Return all the entities of a given type

- apply_all()
  * Call a function for every entity of a given type

- update()

- draw()
*/

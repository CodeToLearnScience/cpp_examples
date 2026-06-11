/*
--------------------------------------
 Entity Manager and Object Creation
--------------------------------------
- create() member function**
  * Creates a new entity object
  * Adds it to all_entities
  * Adds an alias to the object to grouped_entities
- The arguments to create() are used to construct the object
- Different entities require different numbers and types of arguments

-----------------------------------
 entity_manager::create()
-----------------------------------
- We will use a variadic template
- We will use perfect forwarding for efficiency
   template <typename T, typename... Args>
   T& create(Args&&... args);
- The arguments will be forwarded to the entity's constructor
  Example: Create a ball object**
  manager.create<ball>(x, y);

----------------------------------
 entity_manager::grouped_entities
----------------------------------
- grouped_entities is an std::map
- We use type_info::hash_code() for the key of the map
  * This generates a unique number for each derived class
- The value of the map is an std::vector<entity*>
  * These pointers are aliases to the entities in the game
  * Non-owning pointers
  * Must not be used after the entities have been deleted

----------------------------------------
 entity_manager::create() Pseudo-code
----------------------------------------
- Call make_unique() to create the entity object on the heap
  * Use std::forward() to forward the arguments to the constructor
- Insert the unique_ptr into the all_entities vector
- Obtain an alias pointer to the entity object
- Find the hash code of the entity type
- Look up the hash code in the grouped_entities map
- Insert the alias pointer into the map's vector
- Return the new entity object

*/

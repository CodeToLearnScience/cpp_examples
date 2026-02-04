/*
 ------------------------------
 Sequential Containers
 ------------------------------
 - std::string and std::vector are Sequential Containers
 - In a sequential container, the data is stored in an order which is determined
 by the program
   * The order of the data does not depend on its value
   * The data will remain in the same position unless the program performs some
     action which changes them
- Sequential containers are useful for storing data in an order which we can
chose
  * Usually, we can access data by its position

--------------------------
Associative Containers
--------------------------
- In an Associative Containers, the order depends on the data
  * Each element has a "key" which identifies it
  * The key is used to look up an element in the container
  * The key also determines the positionof the element
- Associative Containers are useful for storing information which we want to be
able to search

-----------------
Sets and Maps
-----------------
- C++ provides two types of associative containers
- A set is an unstructured collection of elements
  * An element is a single data item consisting of key nothing else
  * The key is used to check if the data item is present in the collection
- A map is similar to "dictionary" or a "hash map" in other languages
  * An element consists of a pair of data items, a key and a value
  * The key is used to search for an element and look up its value
- So "Set" has only keys and "Map" has both keys and values

-----------------------------------
Associative Containers Operations
-----------------------------------
- Associative containers do not support push_back() and push_front()
  * The position of an element is determined by its key
- They do support many container operations
  * We can insert() and erase() to add and remove elements
  * We can use iterators to loop over the container
- They have member functions which are similar to generic algorithms

----------------------------
Container Adaptors
----------------------------
- The STL also defines some "container adaptors"
- These are data structures (queues and stacks) which are implemented using
sequential containers
- Data is stored in these containers in an order which depends on when the data
was added
 */

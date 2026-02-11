/*
-----------------
Emplacement
-----------------
- C++ introduced emplacement
  * Another way to add elements to containers
- Member functions like push_back() and insert() require an existing object
  * The container copies the existing object into the new element
  * If there is no existing object, we need to create a temporary object
- With emplacement, the container creates the object in the new element, instead
of copying it
   * this avoid the copy constructor call

------------------
Drawback of insert
------------------
- insert() copies its argument into the newly-created element
  * If we want to insert a new object, we have to create a temporary variable
    vector<refrigerator> vec;
    refrigerator fridge(2, false, false); //create a refrigerator object
    vec.insert(begin(vec), frigge);   //Add an element and copy fridge into it
                                      //frigge is not used again

    //add an element create a temporary object and copy it into the new element
    //and refrigerator object gets destroyed when insert returns. This is
    //slightly better
     vec.insert(end(vec), refrigerator(2,false,false));

----------
emplace
----------
- C++11 has emplace()
  * We pass the arguments to the constructor as part of the emplace call

    //refrigerator fridge(2,false,false); //create a refrigerator object
    //vec.insert(begin(vec), fridge); //add an element and copy fridge into it

    vec.emplace(begin(vec), 2, false, true); //add an element and create an
                                             //object in it
  * so we have the iterator, constructor arguments. So the vector will create a
    new element, then it will call the constructor for "refrigerator", with
    these as the arguments to the constructor. And that will create a new object
    in the new element, avoiding any copying

-------------------
emplace() and push()
-------------------
- For containers that support push_back(), there is emplace_back()
- This adds an element at the back of the container and creates a new object in
it
  vec.push_back(refrigerator(2,false,true));
  vec.emplace_back(2,false,true);
- There is also emplate_front(), for containers that support push_front()
- emplace() for container adapter instead of push()

----------------------------
Emplacement with std::map
----------------------------
- Emplacement works differently with containers that have unique keys
  * for std::set and std::map, emplace() creates a temporary object
  * It then checks if there is an element with the same key
- C++17 provides an improved version of emplace() for maps
  * try_emplace() checks for duplicates before creating the new element object
  * If there is an element with the same key, nothing happens

----------------
try_emplace()
----------------
- try_emplace() performs "piece-wise" construction of the map's std::pair
  * The "first" and "second" members are initialized using their constructors
- The first argument to try_emplace() is the new elements key
- The remaining arguments are the arguments to the value's constructor
- The returned value is the same as insert()
    auto[iter, success] = fridges.try_emplace("Not is use"s, 5, false, false);
    if(success){
        ---
    }

------------------------------
Pros and Cons of Emplacement
------------------------------
- Emplacement is the only way to insert objects which cannot be copied
- Emplacement will cause a temporary object to be created if
  * The container does not allow duplicates (std::set and std::map)
  * The implementation uses assignment rather than copying
  * A type conversion is required
- Compilers can often optimize away the copy in insert()
- Move semantics can avoid copying temporary objects
  * So emplacement would probably have been very useful in C++98 but in C++11
    it is, probably, a bit doubtful.
*/

#include <ios>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class refrigerator {
  // data members
  int temperature;
  bool door_open;
  bool power_on;

public:
  refrigerator(int temp, bool open, bool power)
      : temperature(temp), door_open(open), power_on(power) {}
  void print() const {
    cout << "Temperature = " << temperature;
    cout << boolalpha;
    cout << ", door_open = " << door_open;
    cout << ", power_on = " << door_open;
  }
};

int main() {
  vector<refrigerator> vec;

  refrigerator fridge(2, false, true);
  vec.insert(begin(vec), fridge); // add an element and copy frigge into it

  vec.insert(end(vec), refrigerator(3, false, true));
  vec.emplace(end(vec), 5, false,
              false); // add an element and create an object to it
  cout << "Vector elements:\n";
  for (auto el : vec) {
    el.print();
    cout << "\n";
  }

  cout << "\n With push_back() and emplace_back()\n";
  refrigerator fridge2(6, false, true);
  vec.push_back(fridge2);

  vec.push_back(refrigerator(3, false, true));
  vec.emplace_back(5, false, false);
  for (auto el : vec) {
    el.print();
    cout << "\n";
  }

  cout << "\nExample with map and try_emplace():\n";
  map<string, refrigerator> fridges;
  refrigerator meat_fridge(2, false, false);
  fridges.insert_or_assign("Meat fridge"s, meat_fridge);
  fridges.insert_or_assign("Dairy fridge"s, refrigerator(3, false, true));

  auto [iter, success] = fridges.try_emplace("Not in use"s, 5, false, false);

  if (success) {
    cout << "Inserted the new element\n";
  } else {
    auto [name, fridge] = *iter;
    cout << "Insert failed: ";
    cout << "existing element with name " << name << " and data ";
    fridge.print();
    cout << "\n";
  }
}

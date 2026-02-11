#include <iostream>
#include <map>
#include <string>

using namespace std;
using level_map = map<int, string>;

void print(const map<int, level_map> &game_map) {

  cout << "Game map\n";
  for (const auto &level : game_map) {
    cout << "Level number " << level.first << " map: " << "\n";
    for (const auto &elem : level.second) {
      cout << elem.first << ", " << elem.second << "\n";
    }
  }
}

int main() {
  map<int, string> level_one_map = {{1, "player"}, // element with key1
                                    {10, "door"}}; // element with key 10

  level_map level_two_map = {{5, "player"},
                             {10, "monster"}}; // create another level map

  // Game map
  map<int, map<int, string>> game_map = {{1, level_one_map},
                                         {2, level_two_map}};

  print(game_map);
  // c++17
  cout << "\n------printing with C++17-----------------\n";
  for (const auto &[l_no, l_map] : game_map) {
    cout << "Level " << l_no << " map:" << "\n";
    for (const auto &[pos, obj] : l_map) {
      cout << "position = " << pos << ", object = " << obj << "\n";
    }
  }

  cout << "\nInserting a new entity into level 2\n";
  auto level2 = game_map.find(2); // iterator to the level 2 element

  if (level2 != end(game_map)) {
    level2->second.insert({3, "magic wand"});
  }

  print(game_map);

  cout << "\nInserting a new level\n";
  level_map level_three_map = {{7, "player"}, {8, "bomb"}};
  game_map.insert({3, level_three_map});

  print(game_map);

  cout << "\nRemoving element with key 10 from level 2\n";
  auto &lmap = level2->second;
  auto ten = lmap.find(10);
  if (ten != end(lmap)) {
    lmap.erase(ten);
  }
  print(game_map);
}

// Main ideas are
// 1. High-level modules should not depend on low-level modules. Both should
// depend on abstractions
// 2. Abstractions should not depend on details. Details should depend on
// abstractions

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace without_dependency_inversion {

enum class Relationship { parent, child, sibling };

struct Person {
  string name;
};

struct Relationships { // low-level
  vector<tuple<Person, Relationship, Person>> relations;
  void add_perent_and_child(const Person &parent, const Person &child) {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }
};

// lets say now we want to implement high-level module research
struct Research {
  Research(Relationships &relationship) {
    auto &relations = relationship.relations;
    for (auto &&[first, rel, second] : relations) {
      if (first.name == "John" && rel == Relationship::parent) {
        cout << "John has a child named " << second.name << "\n";
      }
    }
  }
};

void example() {
  Person parent{"John"};
  Person child1{"Chris"}, child2{"Matt"};
  Relationships relations;
  relations.add_perent_and_child(parent, child1);
  relations.add_perent_and_child(parent, child2);
  Research _(relations);
}

} // namespace without_dependency_inversion

namespace with_dependency_inversion {
// in previous exmaple, if low-level class makes vector of tuple private or
// if they want to change the data structure, then high-level code Research
// which depends on low-level module will be broken

// so dependency inversion protects high-level implementation from low-level
// details

using namespace without_dependency_inversion;
struct RelationshipBrowser {
  virtual vector<Person> find_all_children_of(const string &name) = 0;
};

struct Relationships : RelationshipBrowser { // low-level
  vector<tuple<Person, Relationship, Person>> relations;
  void add_perent_and_child(const Person &parent, const Person &child) {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

  vector<Person> find_all_children_of(const string &name) override {
    vector<Person> res;
    for (auto &&[first, rel, second] : relations) {
      if (first.name == name && rel == Relationship::parent) {
        res.push_back(second);
      }
    }
    return res;
  }
};

struct Research {
  Research(RelationshipBrowser &browser) {
    for (auto &child : browser.find_all_children_of("John")) {
      cout << "John has a child called " << child.name << "\n";
    }
  }
};

void example() {
  Person parent{"John"};
  Person child1{"Chris"}, child2{"Matt"};
  Relationships relations;
  relations.add_perent_and_child(parent, child1);
  relations.add_perent_and_child(parent, child2);
  Research _(relations);
}
} // namespace with_dependency_inversion

int main() {
  without_dependency_inversion::example();
  with_dependency_inversion::example();
}

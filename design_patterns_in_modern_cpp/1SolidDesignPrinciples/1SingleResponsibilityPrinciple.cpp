#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

struct Journal {
  std::string title;
  std::vector<std::string> entries;
  Journal(std::string title) : title(std::move(title)) {}
  void add_entry(std::string entry) {
    static int count = 1;
    entries.push_back(boost::lexical_cast<std::string>(count++) + " : " +
                      std::move(entry));
  }
};

// if you want to store journal to file, then by the principle of separation of
// concern, we can create a new class to save jounral. So that this can be used
// to some other objects instead of having it inside Journal class and it works
// only with that
// So single responsibility both for jounral and PersistenceManager
struct PersistenceManager {
  static void save(const Journal &journal, const std::string &file_name) {
    std::ofstream ofs(file_name);
    for (const auto &e : journal.entries) {
      ofs << e << "\n";
      ;
    }
  }
};

int main() {
  Journal journal{"My journal"};

  journal.add_entry("Woke up at 6 AM");
  journal.add_entry("Ate idly");

  PersistenceManager::save(journal, "dairy");
}

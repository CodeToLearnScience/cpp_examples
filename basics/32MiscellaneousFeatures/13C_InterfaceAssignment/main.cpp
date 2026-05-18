extern "C" {
#include "print_array.h"
}
#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

int main() {
  std::set<int> s{3, 4, 5, 9};
  std::vector<int> v;
  v.reserve(s.size());

  for (auto it : s) {
    v.push_back(it);
  }

  std::map<int, int> m;
  m.insert(std::make_pair(1, 3));
  m.insert(std::make_pair(2, 1));
  m.insert(std::make_pair(3, 4));

  std::vector<int> m_keys;
  m_keys.reserve(m.size());
  std::vector<int> m_val;
  m_val.reserve(m.size());

  for (auto it : m) {
    m_keys.push_back(it.first);
    m_val.push_back(it.second);
  }

  std::cout << "Printing keys from set data structure C func\n";
  print_array(v.data(), static_cast<int>(v.size()));
  std::cout << "Printing map keys from C func\n";
  print_array(m_keys.data(), static_cast<int>(m_keys.size()));
  std::cout << "Printing map values from C func\n";
  print_array(m_val.data(), static_cast<int>(m_val.size()));
}

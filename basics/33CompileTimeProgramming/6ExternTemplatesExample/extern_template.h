#pragma once
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

template <typename T> std::ostream &print(std::ostream &os, const T &t) {
  return os << t;
}
// So any source file which include this header will know that the instantiation
// is done somewhere else.
extern template std::ostream &print(std::ostream &os, const std::string &str);
void func(const std::string &str);

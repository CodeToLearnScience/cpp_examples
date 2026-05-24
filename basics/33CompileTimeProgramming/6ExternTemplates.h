#pragma once
#include <fstream>
#include <iostream>
#include <string>

// Template declaration only
template <typename T> std::ostream &print(std::ostream &os, const T &t);

// declare non-template function
void func(const std::string &str);

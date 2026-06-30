#include <boost/filesystem.hpp>
#include <boost/system/error_code.hpp>
#include <iostream>

namespace fs = boost::filesystem;

int main() {
  fs::path p("/tmp");

  std::cout << "Path: " << p << std::endl;
  std::cout << "Exists: " << fs::exists(p) << std::endl;

  if (fs::is_directory(p)) {
    std::cout << "It's a directory" << std::endl;
  }

  return 0;
}

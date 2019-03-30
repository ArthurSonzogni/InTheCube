#include "LevelListLoader.hpp"
#include <fstream>
#include <iostream>

#ifdef __EMSCRIPTEN__
#define P "./"
#else
#define P "../"
#endif

std::vector<std::string> LevelListLoader() {
  std::ifstream file(P"lvl/LevelList");
  if (!file) {
    std::cerr << "No level list file" << std::endl;
    return {};
  }

  std::vector<std::string> result;
  std::string line;
  while (getline(file, line)) {
    result.push_back(P"lvl/" + line);
  }
  return result;
}

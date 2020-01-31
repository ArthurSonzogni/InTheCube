#include "game/LevelListLoader.hpp"
#include <fstream>
#include <iostream>

#include "game/Resource.hpp"

std::vector<std::string> LevelListLoader() {
  std::ifstream file(ResourcePath() + "/lvl/LevelList");
  if (!file) {
    std::cerr << "No level list file" << std::endl;
    return {};
  }

  std::vector<std::string> result;
  std::string line;
  while (getline(file, line)) {
    result.push_back(ResourcePath() + "/lvl/" + line);
  }
  return result;
}

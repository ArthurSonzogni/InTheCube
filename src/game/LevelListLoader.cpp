// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

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

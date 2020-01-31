#include "game/SaveManager.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

bool intOf(int& t, const std::string& s);

void SaveManager::Load(std::string savFile) {
  fileName = savFile;

  std::ifstream file(fileName.c_str());
  if (!file)
    return;
  std::string ligne;
  while (getline(file, ligne)) {
    std::string name = ligne;
    int level;
    getline(file, ligne);
    intOf(level, ligne);
    saveList[name] = level;
  }
}

void SaveManager::Sync() {
  std::ofstream file(fileName.c_str());
  if (!file)
    return;

  for(auto& it : saveList) {
    file << it.first << std::endl;
    file << it.second << std::endl;
  }
#ifdef __EMSCRIPTEN__
  EM_ASM(FS.syncfs(false, function(err){console.log(err)});, 0);
#endif
}

bool intOf(int& t, const std::string& s) {
  std::istringstream iss(s);
  return !(iss >> std::dec >> t).fail();
}

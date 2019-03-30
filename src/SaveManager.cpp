#include "SaveManager.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

bool intOf(int& t, const std::string& s);

SaveManager::SaveManager(std::string savFile) {
  fileName = savFile;
  std::ifstream file(savFile.c_str());
  if (!file)
    return;
  std::string ligne;
  while (getline(file, ligne)) {
    Save s;
    s.name = ligne;
    getline(file, ligne);
    intOf(s.level, ligne);
    saveList.push_back(s);
    std::cout << "s.level = " << s.level << " s.name = " << s.name;
  }
}

void SaveManager::Sync() {
  std::ofstream file(fileName.c_str());
  if (!file)
    return;
  for (std::list<Save>::iterator it = saveList.begin(); it != saveList.end();
       it++) {
    file << (*it).name << std::endl << (*it).level << std::endl;
  }
}

bool intOf(int& t, const std::string& s) {
  std::istringstream iss(s);
  return !(iss >> std::dec >> t).fail();
}

void SaveManager::NewProfile(std::string name) {
  Save s;
  s.name = name;
  s.level = 0;
  saveList.push_back(s);
  Sync();
}

void SaveManager::DeleteProfile(std::string name) {
  for (std::list<Save>::iterator it = saveList.begin(); it != saveList.end();
       it++) {
    if ((*it).name == name) {
      saveList.erase(it);
      Sync();
      return;
    }
  }
  return;
}

bool SaveManager::ExistProfile(std::string name) {
  for(const auto& it : saveList) {
    if (it.name == name)
      return true;
  }
  return false;
}

void SaveManager::SetLevel(std::string name, int level) {
  for (std::list<Save>::iterator it = saveList.begin(); it != saveList.end();
       it++) {
    if ((*it).name == name) {
      (*it).level = level;
      Sync();
      return;
    }
  }
}

int SaveManager::GetLevel(std::string name) {
  for (std::list<Save>::iterator it = saveList.begin(); it != saveList.end();
       it++) {
    if ((*it).name == name) {
      return (*it).level;
    }
  }
  return -1;
}

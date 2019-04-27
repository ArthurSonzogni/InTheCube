#include "SaveManager.hpp"
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
#ifdef __EMSCRIPTEN__
  int slash_position = -1;
  for (int i = 0; i < (int)fileName.size(); ++i) {
    if (fileName[i] == '/')
      slash_position = i;
  }
  fileName = "/sav/" + fileName.substr(slash_position + 1, -1);
#endif

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

//void SaveManager::NewProfile(std::string name) {
  //Save s;
  //s.name = name;
  //s.level = 0;
  //saveList.push_back(s);
  //Sync();
//}

//void SaveManager::DeleteProfile(std::string name) {
  //for (std::list<Save>::iterator it = saveList.begin(); it != saveList.end();
       //it++) {
    //if ((*it).name == name) {
      //saveList.erase(it);
      //Sync();
      //return;
    //}
  //}
  //return;
//}

//bool SaveManager::ExistProfile(std::string name) {
  //for(const auto& it : saveList) {
    //if (it.name == name)
      //return true;
  //}
  //return false;
//}

//void SaveManager::SetLevel(std::string name, int level) {
  //for (std::list<Save>::iterator it = saveList.begin(); it != saveList.end();
       //it++) {
    //if ((*it).name == name) {
      //(*it).level = level;
      //Sync();
      //return;
    //}
  //}
//}

//int SaveManager::GetLevel(std::string name) {
  //for (std::list<Save>::iterator it = saveList.begin(); it != saveList.end();
       //it++) {
    //if ((*it).name == name) {
      //return (*it).level;
    //}
  //}
  //return -1;
//}

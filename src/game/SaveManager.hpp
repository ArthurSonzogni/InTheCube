// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_SAVE_MANAGER_HPP
#define GAME_SAVE_MANAGER_HPP

#include <map>
#include <string>

struct Save {
  std::string name;
  int level;
};

class SaveManager {
 public:
  void Load(std::string savFile);
  // void NewProfile(std::string name);
  // void DeleteProfile(std::string name);
  // void SetLevel(std::string name, int level);
  // int GetLevel(std::string name);
  void Sync();
  // bool ExistProfile(std::string name);

  std::map<std::string, int> saveList;

 private:
  std::string fileName;
};

#endif /* GAME_SAVE_MANAGER_HPP */

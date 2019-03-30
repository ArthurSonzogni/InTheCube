#ifndef SAVE_MANAGER_HPP
#define SAVE_MANAGER_HPP

#include <list>
#include <string>

struct Save {
  std::string name;
  int level;
};

class SaveManager {
 public:
  std::list<Save> saveList;

 private:
  std::string fileName;

 public:
  SaveManager(std::string savFile);
  void NewProfile(std::string name);
  void DeleteProfile(std::string name);
  void SetLevel(std::string name, int level);
  int GetLevel(std::string name);
  void Sync();
  bool ExistProfile(std::string name);
};

#endif /* SAVE_MANAGER_HPP */

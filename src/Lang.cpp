#include "Lang.hpp"

#include <fstream>
#include <iostream>
#include <map>

std::map<std::wstring, std::wstring> textMap;

void LoadTraduction(std::string fileName) {
  std::wifstream file(fileName.c_str());
  std::wstring text;
  std::wstring id;
  if (!file) {
    std::cerr << "file " << fileName << " not found" << std::endl;
    return;
  }

  while (std::getline(file, id)) {
    std::getline(file, text);
    textMap[id] = text;
  }
}

std::wstring tr(std::wstring id) {
  return textMap[id];
}

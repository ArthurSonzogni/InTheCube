// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "game/Lang.hpp"

#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <map>

#include "string.hpp"

std::map<std::wstring, std::wstring> textMap;
void LoadTraduction(std::string fileName) {
  std::ifstream file(fileName.c_str());
  if (!file)
    return;

  std::string id;
  while (std::getline(file, id)) {
    std::string text;
    std::getline(file, text);
    textMap[to_wstring(id)] = to_wstring(text);
  }
}

std::wstring tr(std::wstring id) {
  return textMap[id];
}

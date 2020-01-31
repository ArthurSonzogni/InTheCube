#include "game/Lang.hpp"

#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <map>

namespace {
std::wstring to_wstring(const std::string& s) {
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  return converter.from_bytes(s);
}
}  // namespace

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

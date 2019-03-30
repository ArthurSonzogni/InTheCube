#ifndef TEXT_POPUP_HPP
#define TEXT_POPUP_HPP

#include <string>
#include <vector>
#include "Forme.hpp"
#include "Sprite.hpp"

class Screen;

class TextPopup {
 public:
  std::vector<std::vector<std::wstring>> text;
  int pos;
  int taille;
  Rectangle geometry;
  std::string textString;
  Sprite spaceSprite;

  TextPopup(int type);
  void Draw(Screen& screen);
  void DrawAux(Screen& screen, int p);
};

#endif /* TEXT_POPUP_HPP */

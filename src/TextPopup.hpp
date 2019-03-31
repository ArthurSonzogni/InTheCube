#ifndef TEXT_POPUP_HPP
#define TEXT_POPUP_HPP

#include <string>
#include <vector>
#include "Forme.hpp"
#include <smk/Sprite.hpp>

namespace smk {
class Screen;
}  // namespace smk

class TextPopup {
 public:
  std::vector<std::vector<std::wstring>> text;
  int pos;
  int taille;
  Rectangle geometry;
  std::string textString;
  smk::Sprite spaceSprite;

  TextPopup(int type);
  void Draw(smk::Screen& screen);
  void DrawAux(smk::Screen& screen, int p);
};

#endif /* TEXT_POPUP_HPP */

#ifndef TEXT_POPUP_HPP
#define TEXT_POPUP_HPP

#include <smk/Sprite.hpp>
#include <smk/Text.hpp>
#include <string>
#include <vector>
#include "Forme.hpp"

namespace smk {
class Screen;
}  // namespace smk

class TextPopup {
 public:
  TextPopup(int type);
  bool Step(smk::Screen& screen);
  void Draw(smk::Screen& screen);
  Rectangle geometry;

 private:
  std::vector<std::vector<std::wstring>> text;
  smk::Text textString;
  smk::Sprite spaceSprite;

  int p = 0;
  int time = 0;
  int horizontal_shift = 640;
};

#endif /* TEXT_POPUP_HPP */

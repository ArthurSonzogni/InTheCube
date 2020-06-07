// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_TEXT_POPUP_HPP
#define GAME_TEXT_POPUP_HPP

#include <smk/Sprite.hpp>
#include <smk/Text.hpp>
#include <string>
#include <vector>

#include "game/Forme.hpp"

namespace smk {
class Window;
}  // namespace smk

class TextPopup {
 public:
  TextPopup(int type);
  bool Step(smk::Window& window);
  void Draw(smk::Window& window);
  Rectangle geometry;

 private:
  std::vector<std::vector<std::wstring>> text;
  smk::Text textString;
  smk::Sprite spaceSprite;

  int p = 0;
  int time = 0;
  int horizontal_shift = 640;
};

#endif /* GAME_TEXT_POPUP_HPP */

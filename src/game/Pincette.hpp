// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_PINCETTE_HPP
#define GAME_PINCETTE_HPP

#include <smk/Sprite.hpp>

#include "game/Resource.hpp"

namespace smk {
class Window;
}  // namespace smk

class Pincette {
 public:
  Pincette();
  void Step();
  void Draw(smk::Window& window);

 private:
  int step_ = 0;
  smk::Sprite pincetteSprite;
  smk::Sprite heroSprite;
};

#endif /* GAME_PINCETTE_HPP */

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_CREEPER_HPP
#define GAME_CREEPER_HPP

#include <smk/Sprite.hpp>

#include "game/Forme.hpp"

namespace smk {
class Window;
}  // namespace smk

class Creeper {
 public:
  float x, y, xspeed, yspeed;
  int mode;
  smk::Sprite sprite;
  Rectangle geometry;
  int t;

  Creeper(int x, int y);
  void Draw(smk::Window& window);
  void UpdateGeometry();
};

#endif /* GAME_CREEPER_HPP */

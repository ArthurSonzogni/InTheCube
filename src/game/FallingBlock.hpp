// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_FALLING_BLOCK_HPP
#define GAME_FALLING_BLOCK_HPP

#include <smk/Sprite.hpp>

#include "game/Forme.hpp"

namespace smk {
class Window;
}  // namespace smk

class FallingBlock {
 public:
  FallingBlock(float X, float Y);
  Rectangle geometry;
  smk::Sprite sprite;
  void UpdateGeometry();
  void Draw(smk::Window& window);
  float x, y;
  float yspeed;
  int etape;
};

#endif /* GAME_FALLING_BLOCK_HPP */

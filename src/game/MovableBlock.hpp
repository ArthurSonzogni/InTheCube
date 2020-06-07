// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_MOVABLE_BLOCK_HPP
#define GAME_MOVABLE_BLOCK_HPP

#include <smk/Sprite.hpp>

#include "game/Forme.hpp"

namespace smk {
class Window;
}  // namespace smk

class MovableBlock {
 public:
  Rectangle geometry;
  smk::Sprite sprite;
  float x, y, xspeed, yspeed;

  MovableBlock(int x, int y);
  void UpdateGeometry();
  void Draw(smk::Window& window);
};

#endif /* GAME_MOVABLE_BLOCK_HPP */

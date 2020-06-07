// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_MOVING_BLOCK_HPP
#define GAME_MOVING_BLOCK_HPP

#include <smk/Sprite.hpp>

#include "game/Forme.hpp"
namespace smk {
class Window;
}  // namespace smk

class MovingBlock {
 public:
  Rectangle geometry;
  smk::Sprite sprite;
  int xtile, ytile;
  bool tiled;
  float x, y;
  float xspeed;
  float yspeed;
  float width;
  float height;

  MovingBlock(int X, int Y, int WIDTH, int HEIGHT, float XSPEED, float YSPEED);
  void UpdateGeometry();
  void Draw(smk::Window& window);
};

#endif /* GAME_MOVING_BLOCK_HPP */

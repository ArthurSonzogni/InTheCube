// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "game/MovableBlock.hpp"

#include <smk/Window.hpp>

#include "game/Resource.hpp"

MovableBlock::MovableBlock(int X, int Y) {
  x = X;
  y = Y;
  yspeed = 0;
  xspeed = 0;
  geometry.left = X;
  geometry.top = Y;
  geometry.right = X + 31;
  geometry.bottom = Y + 31;
  sprite = smk::Sprite(img_block1);
  sprite.SetPosition(X, Y);
}
void MovableBlock::UpdateGeometry() {
  geometry.left = x;
  geometry.top = y;
  geometry.right = x + 31;
  geometry.bottom = y + 31;
  sprite.SetPosition(x, y);
}

void MovableBlock::Draw(smk::Window& window) {
  window.Draw(sprite);
}

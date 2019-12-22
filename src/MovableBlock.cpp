#include "MovableBlock.hpp"
#include "Resource.hpp"
#include <smk/Window.hpp>

MovableBlock::MovableBlock(int X, int Y) {
  x = X;
  y = Y;
  yspeed = 0;
  xspeed = 0;
  geometry.left = X;
  geometry.top = Y;
  geometry.right = X + 31;
  geometry.bottom = Y + 31;
  sprite.SetTexture(img_block2);
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

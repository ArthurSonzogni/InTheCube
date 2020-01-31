#include "game/Glass.hpp"
#include "game/Resource.hpp"
#include <smk/Window.hpp>

Glass::Glass(int X, int Y) {
  x = X;
  y = Y;
  yspeed = 0;
  xspeed = 0;
  geometry.left = X;
  geometry.top = Y;
  geometry.right = X + 31;
  geometry.bottom = Y + 31;
  sprite = smk::Sprite(img_glass);
  sprite.SetPosition(X, Y);
  height = 31;
  width = 31;
}
void Glass::UpdateGeometry() {
  geometry.left = x;
  geometry.top = y;
  geometry.right = x + width;
  geometry.bottom = y + height;
  sprite.SetPosition(x, y);
  sprite.SetScale(width / 31, height / 31);
}

void Glass::Draw(smk::Window& window) {
  window.Draw(sprite);
}

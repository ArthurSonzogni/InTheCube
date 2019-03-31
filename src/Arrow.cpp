#include "Arrow.hpp"

#include <cmath>
#include <smk/Screen.hpp>
#include "Resource.hpp"

Arrow::Arrow(float X, float Y, float Xspeed, float Yspeed) {
  x = X;
  y = Y;
  xspeed = Xspeed;
  yspeed = Yspeed;
  sprite.SetTexture(img_arrow);
  sprite.SetRotation(std::atan2(-yspeed, xspeed) * 57.3);
  sprite.SetPosition(x, y);
  sprite.SetCenter(24, 8);
  geometry.x = x;
  geometry.y = y;
  damage = false;
  alpha = 255;
}

void Arrow::Step() {
  x += xspeed;
  y += yspeed;
  geometry.x = x;
  geometry.y = y;
}

void Arrow::Draw(smk::Screen& screen) {
  sprite.SetPosition(x, y);
  screen.Draw(sprite);
}

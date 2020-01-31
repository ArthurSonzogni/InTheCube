#include "game/FallingBlock.hpp"
#include <smk/Window.hpp>
#include "game/Resource.hpp"

FallingBlock::FallingBlock(float X, float Y) {
  x = X;
  y = Y;
  yspeed = 0;
  geometry.left = X;
  geometry.top = Y;
  geometry.right = X + 31;
  geometry.bottom = Y + 31;
  sprite = smk::Sprite(img_block2);
  sprite.SetPosition(X, Y);
  etape = 0;
}

float SinusSintoide(int i) {
  float tab[9] = {0, 1, 1.5, 1, 0, -1, -1.5, -1, 0};
  return tab[i % 9];
}

void FallingBlock::UpdateGeometry() {
  geometry.left = x;
  geometry.top = y;
  geometry.right = x + 31;
  geometry.bottom = y + 31;
  sprite.SetPosition(x, y);
}
void FallingBlock::Draw(smk::Window& window) {
  if (etape != 0 and etape <= 15) {
    sprite.Move(SinusSintoide(etape), 0);
    window.Draw(sprite);
    sprite.Move(-SinusSintoide(etape), 0);
  } else {
    window.Draw(sprite);
  }
}

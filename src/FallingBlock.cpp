#include "FallingBlock.hpp"
#include "Resource.hpp"
#include <smk/Screen.hpp>

FallingBlock::FallingBlock(float X, float Y) {
  x = X;
  y = Y;
  yspeed = 0;
  geometry.left = X;
  geometry.top = Y;
  geometry.right = X + 31;
  geometry.bottom = Y + 31;
  sprite.SetTexture(img_block2);
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
void FallingBlock::Draw(smk::Screen& screen) {
  if (etape != 0 and etape <= 15) {
    sprite.Move(SinusSintoide(etape), 0);
     screen.Draw(sprite);
    sprite.Move(-SinusSintoide(etape), 0);
  } else {
     screen.Draw(sprite);
  }
}

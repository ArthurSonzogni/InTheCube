#include "Cloner.hpp"
#include "Resource.hpp"
#include "Screen.hpp"

Cloner::Cloner(int Xstart, int Ystart, int Xend, int Yend) {
  xstart = Xstart;
  ystart = Ystart;
  xend = Xend;
  yend = Yend;
  sprite.SetTexture(img_cloneur);
  sprite.SetPosition(xstart, ystart);
  enable = true;
}

void Cloner::Draw(Screen& screen) {
  sprite.SetPosition(xstart, ystart);
  screen.Draw(sprite);
  sprite.SetPosition(xend, yend);
  screen.Draw(sprite);
}

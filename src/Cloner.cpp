#include "Cloner.hpp"
#include "Resource.hpp"
#include <smk/Window.hpp>

Cloner::Cloner(int Xstart, int Ystart, int Xend, int Yend) {
  xstart = Xstart;
  ystart = Ystart;
  xend = Xend;
  yend = Yend;
  sprite.SetTexture(img_cloneur);
  sprite.SetPosition(xstart, ystart);
  enable = true;
}

void Cloner::Draw(smk::Window& window) {
  sprite.SetPosition(xstart, ystart);
  window.Draw(sprite);
  sprite.SetPosition(xend, yend);
  window.Draw(sprite);
}

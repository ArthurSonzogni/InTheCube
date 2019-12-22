#include "ArrowLauncher.hpp"

#include "Resource.hpp"
#include <smk/Window.hpp>

ArrowLauncher::ArrowLauncher(float X, float Y, float O) {
  x = X;
  y = Y;
  orientation = O;
  sprite.SetTexture(img_arrowLauncher);
  sprite.SetPosition(x, y);
  sound.SetBuffer(SB_arrowLauncher);
  sound.SetLoop(false);
}

void ArrowLauncher::Draw(smk::Window& window) {
  window.Draw(sprite);
}

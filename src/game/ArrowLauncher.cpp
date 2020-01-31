#include "ArrowLauncher.hpp"

#include "game/Resource.hpp"
#include <smk/Window.hpp>

ArrowLauncher::ArrowLauncher(float X, float Y, float O) {
  sprite = smk::Sprite(img_arrowLauncher);
  sound = smk::Sound(SB_arrowLauncher);
  x = X;
  y = Y;
  orientation = O;
  sprite.SetPosition(x, y);
  sound.SetLoop(false);
}

void ArrowLauncher::Draw(smk::Window& window) {
  window.Draw(sprite);
}

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "ArrowLauncher.hpp"

#include <smk/Window.hpp>

#include "game/Resource.hpp"

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

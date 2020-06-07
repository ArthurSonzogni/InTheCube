// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "Cloner.hpp"

#include <smk/Window.hpp>

#include "game/Resource.hpp"

Cloner::Cloner(int Xstart, int Ystart, int Xend, int Yend) {
  xstart = Xstart;
  ystart = Ystart;
  xend = Xend;
  yend = Yend;
  sprite = smk::Sprite(img_cloneur);
  sprite.SetPosition(xstart, ystart);
  enable = true;
}

void Cloner::Draw(smk::Window& window) {
  sprite.SetPosition(xstart, ystart);
  window.Draw(sprite);
  sprite.SetPosition(xend, yend);
  window.Draw(sprite);
}

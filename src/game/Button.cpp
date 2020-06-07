// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "game/Button.hpp"

#include <smk/Sprite.hpp>

#include "game/Resource.hpp"

Button::Button(int x, int y, int n) {
  nb_pressed = 0;
  isPressed = false;
  t = 0;
  geometry.left = x - 4;
  geometry.top = y - 4;
  geometry.right = x + 4;
  geometry.bottom = y + 4;
  nb_pressed_required = n;
}

void Button::Draw(smk::Window& window) {
  smk::Sprite sprite(img_button[nb_pressed]);
  sprite.SetCenter(8, 8);
  sprite.SetPosition(geometry.left + 8, geometry.top + 8);
  window.Draw(sprite);
}

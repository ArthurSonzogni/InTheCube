// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_BUTTON_HPP
#define GAME_BUTTON_HPP

#include <smk/Window.hpp>

#include "game/Forme.hpp"

class Button {
 public:
  Rectangle geometry;
  int nb_pressed;
  int nb_pressed_required;
  bool isPressed;
  int t;

  Button(int x, int y, int n);

  void Draw(smk::Window& window);
};

#endif /* GAME_BUTTON_HPP */

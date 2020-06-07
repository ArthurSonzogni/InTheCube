// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_INVISIBLE_BLOCK_HPP
#define GAME_INVISIBLE_BLOCK_HPP

#include <smk/Window.hpp>

#include "game/Forme.hpp"
#include "game/Hero.hpp"

class InvisibleBlock {
 public:
  Rectangle geometry;
  smk::Sprite sprite;

  InvisibleBlock(int x, int y, int width, int height);
  void Draw(smk::Window& window, const Hero& hero);
};

#endif /* GAME_INVISIBLE_BLOCK_HPP */

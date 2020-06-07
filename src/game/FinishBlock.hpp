// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_FINISH_BLOCK_HPP
#define GAME_FINISH_BLOCK_HPP

#include "game/Forme.hpp"

class FinishBlock {
 public:
  FinishBlock();
  FinishBlock(int x, int y, int width, int height);
  Rectangle geometry;
};

#endif /* GAME_FINISH_BLOCK_HPP */

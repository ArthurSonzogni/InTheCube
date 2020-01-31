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

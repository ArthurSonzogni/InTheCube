#ifndef FINISH_BLOCK_HPP
#define FINISH_BLOCK_HPP

#include "Forme.hpp"

class FinishBlock {
 public:
  FinishBlock();
  FinishBlock(int x, int y, int width, int height);
  Rectangle geometry;
};

#endif /* FINISH_BLOCK_HPP */

#ifndef INVISIBLE_BLOCK_HPP
#define INVISIBLE_BLOCK_HPP

#include "Forme.hpp"
#include "Hero.hpp"
#include "Screen.hpp"

class InvisibleBlock {
 public:
  Rectangle geometry;
  Sprite sprite;

  InvisibleBlock(int x, int y, int width, int height);
  void Draw(Screen& screen, const Hero& hero);
};

#endif /* INVISIBLE_BLOCK_HPP */

#ifndef INVISIBLE_BLOCK_HPP
#define INVISIBLE_BLOCK_HPP

#include "Forme.hpp"
#include "Hero.hpp"
#include <smk/Screen.hpp>

class InvisibleBlock {
 public:
  Rectangle geometry;
  smk::Sprite sprite;

  InvisibleBlock(int x, int y, int width, int height);
  void Draw(smk::Screen& screen, const Hero& hero);
};

#endif /* INVISIBLE_BLOCK_HPP */

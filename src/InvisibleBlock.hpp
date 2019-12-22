#ifndef INVISIBLE_BLOCK_HPP
#define INVISIBLE_BLOCK_HPP

#include "Forme.hpp"
#include "Hero.hpp"
#include <smk/Window.hpp>

class InvisibleBlock {
 public:
  Rectangle geometry;
  smk::Sprite sprite;

  InvisibleBlock(int x, int y, int width, int height);
  void Draw(smk::Window& window, const Hero& hero);
};

#endif /* INVISIBLE_BLOCK_HPP */

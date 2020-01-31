#ifndef GAME_INVISIBLE_BLOCK_HPP
#define GAME_INVISIBLE_BLOCK_HPP

#include "game/Forme.hpp"
#include "game/Hero.hpp"
#include <smk/Window.hpp>

class InvisibleBlock {
 public:
  Rectangle geometry;
  smk::Sprite sprite;

  InvisibleBlock(int x, int y, int width, int height);
  void Draw(smk::Window& window, const Hero& hero);
};

#endif /* GAME_INVISIBLE_BLOCK_HPP */

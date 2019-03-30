#ifndef MOVABLE_BLOCK_HPP
#define MOVABLE_BLOCK_HPP

#include "Forme.hpp"
#include "Sprite.hpp"

class Screen;

class MovableBlock {
 public:
  Rectangle geometry;
  Sprite sprite;
  float x, y, xspeed, yspeed;

  MovableBlock(int x, int y);
  void UpdateGeometry();
  void Draw(Screen& screen);
};

#endif /* MOVABLE_BLOCK_HPP */

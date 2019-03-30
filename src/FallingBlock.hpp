#ifndef FALLING_BLOCK_HPP
#define FALLING_BLOCK_HPP

#include "Forme.hpp"
#include "Sprite.hpp"

class Screen;

class FallingBlock {
 public:
  FallingBlock(float X, float Y);
  Rectangle geometry;
  Sprite sprite;
  void UpdateGeometry();
  void Draw(Screen& screen);
  float x, y;
  float yspeed;
  int etape;
};

#endif /* FALLING_BLOCK_HPP */

#ifndef MOVING_BLOCK_HPP
#define MOVING_BLOCK_HPP

#include "Forme.hpp"
#include "Sprite.hpp"
class Screen;

class MovingBlock {
 public:
  Rectangle geometry;
  Sprite sprite;
  int xtile, ytile;
  bool tiled;
  float x, y;
  float xspeed;
  float yspeed;
  float width;
  float height;

  MovingBlock(int X, int Y, int WIDTH, int HEIGHT, float XSPEED, float YSPEED);
  void UpdateGeometry();
  void Draw(Screen& screen);
};

#endif /* MOVING_BLOCK_HPP */

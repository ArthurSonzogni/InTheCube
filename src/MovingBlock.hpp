#ifndef MOVING_BLOCK_HPP
#define MOVING_BLOCK_HPP

#include "Forme.hpp"
#include <smk/Sprite.hpp>
namespace smk {
class Screen;
}  // namespace smk

class MovingBlock {
 public:
  Rectangle geometry;
  smk::Sprite sprite;
  int xtile, ytile;
  bool tiled;
  float x, y;
  float xspeed;
  float yspeed;
  float width;
  float height;

  MovingBlock(int X, int Y, int WIDTH, int HEIGHT, float XSPEED, float YSPEED);
  void UpdateGeometry();
  void Draw(smk::Screen& screen);
};

#endif /* MOVING_BLOCK_HPP */

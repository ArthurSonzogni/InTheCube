#ifndef GAME_MOVING_BLOCK_HPP
#define GAME_MOVING_BLOCK_HPP

#include "game/Forme.hpp"
#include <smk/Sprite.hpp>
namespace smk {
class Window;
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
  void Draw(smk::Window& window);
};

#endif /* GAME_MOVING_BLOCK_HPP */

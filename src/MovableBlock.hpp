#ifndef MOVABLE_BLOCK_HPP
#define MOVABLE_BLOCK_HPP

#include "Forme.hpp"
#include <smk/Sprite.hpp>

namespace smk {
class Window;
}  // namespace smk

class MovableBlock {
 public:
  Rectangle geometry;
  smk::Sprite sprite;
  float x, y, xspeed, yspeed;

  MovableBlock(int x, int y);
  void UpdateGeometry();
  void Draw(smk::Window& window);
};

#endif /* MOVABLE_BLOCK_HPP */

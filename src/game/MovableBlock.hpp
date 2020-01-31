#ifndef GAME_MOVABLE_BLOCK_HPP
#define GAME_MOVABLE_BLOCK_HPP

#include "game/Forme.hpp"
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

#endif /* GAME_MOVABLE_BLOCK_HPP */

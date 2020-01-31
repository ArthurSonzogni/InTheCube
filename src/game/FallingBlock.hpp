#ifndef GAME_FALLING_BLOCK_HPP
#define GAME_FALLING_BLOCK_HPP

#include "game/Forme.hpp"
#include <smk/Sprite.hpp>

namespace smk {
class Window;
}  // namespace smk

class FallingBlock {
 public:
  FallingBlock(float X, float Y);
  Rectangle geometry;
  smk::Sprite sprite;
  void UpdateGeometry();
  void Draw(smk::Window& window);
  float x, y;
  float yspeed;
  int etape;
};

#endif /* GAME_FALLING_BLOCK_HPP */

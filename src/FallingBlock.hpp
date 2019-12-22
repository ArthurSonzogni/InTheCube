#ifndef FALLING_BLOCK_HPP
#define FALLING_BLOCK_HPP

#include "Forme.hpp"
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

#endif /* FALLING_BLOCK_HPP */

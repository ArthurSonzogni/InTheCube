#ifndef GAME_GLASS_HPP
#define GAME_GLASS_HPP

#include <smk/Sprite.hpp>
#include "game/Forme.hpp"

namespace smk {
class Window;
}  // namespace smk

class Glass {
 public:
  Rectangle geometry;
  smk::Sprite sprite;
  float x, y, xspeed, yspeed;
  float height;
  float width;
  bool in_laser = false;

  Glass(int x, int y);
  void UpdateGeometry();
  void Draw(smk::Window& window);
};

#endif /* GAME_GLASS_HPP */

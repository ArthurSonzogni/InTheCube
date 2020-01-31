#ifndef GAME_CREEPER_HPP
#define GAME_CREEPER_HPP

#include "game/Forme.hpp"
#include <smk/Sprite.hpp>

namespace smk {
class Window;
} // namespace smk

class Creeper {
 public:
  float x, y, xspeed, yspeed;
  int mode;
  smk::Sprite sprite;
  Rectangle geometry;
  int t;

  Creeper(int x, int y);
  void Draw(smk::Window& window);
  void UpdateGeometry();
};

#endif /* GAME_CREEPER_HPP */

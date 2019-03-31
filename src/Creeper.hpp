#ifndef CREEPER_HPP
#define CREEPER_HPP

#include "Forme.hpp"
#include <smk/Sprite.hpp>

namespace smk {
class Screen;
} // namespace smk

class Creeper {
 public:
  float x, y, xspeed, yspeed;
  int mode;
  smk::Sprite sprite;
  Rectangle geometry;
  int t;

  Creeper(int x, int y);
  void Draw(smk::Screen& screen);
  void UpdateGeometry();
};

#endif /* CREEPER_HPP */

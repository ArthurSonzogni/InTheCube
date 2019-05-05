#ifndef GLASS_HPP
#define GLASS_HPP

#include <smk/Sprite.hpp>
#include "Forme.hpp"

namespace smk {
class Screen;
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
  void Draw(smk::Screen& screen);
};

#endif /* GLASS_HPP */

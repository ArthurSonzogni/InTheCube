#ifndef ARROW_HPP
#define ARROW_HPP

#include "Forme.hpp"
#include <smk/Sprite.hpp>

namespace smk {
class Window;
}  // namespace smk

class Arrow {
 public:
  Point geometry;
  float x, y;
  float xspeed, yspeed;
  smk::Sprite sprite;
  bool damage;
  int alpha;

  Arrow(float X, float Y, float Xspeed, float Yspeed);
  void Step();
  void Draw(smk::Window& window);
};

#endif /* ARROW_HPP */

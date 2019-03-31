#ifndef HERO_HPP
#define HERO_HPP

#include "Collision.hpp"
#include "Resource.hpp"
#include <smk/Sprite.hpp>

namespace smk {
class Screen;
}  // namespace smk

class Hero {
 public:
  Rectangle geometry;
  smk::Sprite sprite;
  float x, y;
  float xspeed, yspeed;
  int life;
  bool sens;

  Hero();
  Hero(float x, float y);
  void SetPosition(float x, float y);
  void UpdateGeometry();

  void Draw(smk::Screen& screen);
};

#endif /* HERO_HPP */

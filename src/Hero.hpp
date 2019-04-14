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
  float x = 0.f;
  float y = 0.f;
  float xspeed = 0.f;
  float yspeed = 0.f;
  int life;
  bool sens = true;

  //Hero();
  Hero(float x, float y);
  void SetPosition(float x, float y);
  void UpdateGeometry();

  void Draw(smk::Screen& screen, bool selected);
};

#endif /* HERO_HPP */

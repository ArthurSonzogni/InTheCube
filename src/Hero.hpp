#ifndef HERO_HPP
#define HERO_HPP

#include "Collision.hpp"
#include "Resource.hpp"
#include "Sprite.hpp"

class Screen;

class Hero {
 public:
  Rectangle geometry;
  Sprite sprite;
  float x, y;
  float xspeed, yspeed;
  int life;
  bool sens;

  Hero();
  Hero(float x, float y);
  void SetPosition(float x, float y);
  void UpdateGeometry();

  void Draw(Screen& screen);
};

#endif /* HERO_HPP */

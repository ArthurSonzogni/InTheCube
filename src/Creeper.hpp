#ifndef CREEPER_HPP
#define CREEPER_HPP

#include "Forme.hpp"
#include "Sprite.hpp"

class Screen;

class Creeper {
 public:
  float x, y, xspeed, yspeed;
  int mode;
  Sprite sprite;
  Rectangle geometry;
  int t;

  Creeper(int x, int y);
  void Draw(Screen& screen);
  void UpdateGeometry();
};

#endif /* CREEPER_HPP */

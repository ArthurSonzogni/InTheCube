#ifndef GLASS_HPP
#define GLASS_HPP

#include "Forme.hpp"
#include "Sprite.hpp"
class Screen;

class Glass {
 public:
  Rectangle geometry;
  Sprite sprite;
  float x, y, xspeed, yspeed;
  float height;
  float width;
  Glass(int x, int y);
  void UpdateGeometry();
  void Draw(Screen& screen);
};

#endif /* GLASS_HPP */

#ifndef ARROW_HPP
#define ARROW_HPP

#include "Forme.hpp"
#include "Sprite.hpp"

class Screen;

class Arrow {
 public:
  Point geometry;
  float x, y;
  float xspeed, yspeed;
  Sprite sprite;
  bool damage;
  int alpha;

  Arrow(float X, float Y, float Xspeed, float Yspeed);
  void Step();
  void Draw(Screen& screen);
};

#endif /* ARROW_HPP */

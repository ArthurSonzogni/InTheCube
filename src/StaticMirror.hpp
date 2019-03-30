#ifndef STATIC_MIRROR_HPP
#define STATIC_MIRROR_HPP

#include <cmath>
#include "Forme.hpp"
#include "Sprite.hpp"

class Screen;

#define DEGTORAD 0.0174532925

class StaticMirror {
 public:
  Line geometry;
  Sprite sprite;
  int xattach, yattach;
  int xcenter, ycenter;
  int angle;
  StaticMirror(int x1, int y1, int x2, int y2, int Xattach, int Yattach);
  void Draw(Screen& screen);
};

#endif /* STATIC_MIRROR_HPP */

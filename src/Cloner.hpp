#ifndef CLONER_HPP
#define CLONER_HPP

#include "Sprite.hpp"

class Screen;

class Cloner {
 public:
  int xstart, ystart, xend, yend;
  bool enable;
  Sprite sprite;
  Cloner(int Xstart, int Ystart, int Xend, int Yend);
  void Draw(Screen& screen);
};

#endif /* CLONER_HPP */

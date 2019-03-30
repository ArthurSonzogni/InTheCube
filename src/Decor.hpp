#ifndef DECORS_HPP
#define DECORS_HPP

#include "Sprite.hpp"
class Screen;

class Decor {
 public:
  Sprite sprite;

  Decor(int X, int Y, int IMG);
  void Draw(Screen& screen);
};

#endif /* DECORS_HPP */

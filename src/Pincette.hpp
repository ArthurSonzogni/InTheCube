#ifndef PINCETTE_HPP
#define PINCETTE_HPP

#include "Resource.hpp"
#include "Sprite.hpp"

class Screen;

class Pincette {
 public:
  Pincette();
  void Step();
  void Draw(Screen& screen);

 private:
  int step_ = 0;
  Sprite pincetteSprite;
  Sprite heroSprite;
};

#endif /* PINCETTE_HPP */

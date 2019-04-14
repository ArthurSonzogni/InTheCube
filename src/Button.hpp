#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Forme.hpp"
#include <smk/Screen.hpp>

class Button {
 public:
  Rectangle geometry;
  int nb_pressed;
  int nb_pressed_required;
  bool isPressed;
  int t;

  Button(int x, int y, int n);

  void Draw(smk::Screen& screen);
};

#endif /* BUTTON_HPP */
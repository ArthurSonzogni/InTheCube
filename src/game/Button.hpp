#ifndef GAME_BUTTON_HPP
#define GAME_BUTTON_HPP

#include "game/Forme.hpp"
#include <smk/Window.hpp>

class Button {
 public:
  Rectangle geometry;
  int nb_pressed;
  int nb_pressed_required;
  bool isPressed;
  int t;

  Button(int x, int y, int n);

  void Draw(smk::Window& window);
};

#endif /* GAME_BUTTON_HPP */

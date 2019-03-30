#include "Button.hpp"

Button::Button(int x, int y, int n) {
  nb_pressed = 0;
  isPressed = false;
  t = 0;
  geometry.left = x - 4;
  geometry.top = y - 4;
  geometry.right = x + 4;
  geometry.bottom = y + 4;
  nb_pressed_required = n;
}

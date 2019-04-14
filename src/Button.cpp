#include "Button.hpp"
#include <smk/Sprite.hpp>
#include "Resource.hpp"

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

void Button::Draw(smk::Screen& screen) {
  smk::Sprite sprite;
  sprite.SetTexture(img_button[nb_pressed]);
  sprite.SetCenter(8, 8);
  sprite.SetPosition(geometry.left + 8, geometry.top + 8);
  screen.Draw(sprite);
}

#include "Hero.hpp"
#include <smk/Screen.hpp>
#include <smk/Color.hpp>

//Hero::Hero() {
  //geometry.left = 0;
  //geometry.top = 0;
  //geometry.right = 29;
  //geometry.bottom = 29;
  //sprite.SetTexture(img_hero_right);
  //sprite.SetPosition(0, 0);
  //x = 0;
  //y = 0;
  //xspeed = 0;
  //yspeed = 0;
  //life = 10;
  //sens = true;
//}

Hero::Hero(float X, float Y) {
  geometry.left = X;
  geometry.top = Y;
  geometry.right = X + 29;
  geometry.bottom = Y + 29;
  sprite.SetTexture(img_hero_left);
  sprite.SetPosition(X, Y);
  x = X;
  y = Y;
  xspeed = 0;
  yspeed = 0;
  life = 7;
}

void Hero::SetPosition(float X, float Y) {
  geometry.left = X;
  geometry.top = Y;
  geometry.right = X + 29;
  geometry.bottom = Y + 29;
  sprite.SetPosition(X, Y);
  x = X;
  y = Y;
}

void Hero::Draw(smk::Screen& screen, bool selected) {
  static const glm::vec4 colorNonSelected = {0.78, 0.78, 0.39, 1.f};
  sprite.SetColor(selected ? smk::Color::White : colorNonSelected);
  sprite.SetTexture(sens ? img_hero_left : img_hero_right);
  sprite.SetPosition(x, y);
  screen.Draw(sprite);
}

void Hero::UpdateGeometry() {
  geometry.left = x;
  geometry.right = x + 29;
  geometry.top = y;
  geometry.bottom = y + 29;
}

#include "Laser.hpp"
#include <smk/Color.hpp>
#include <smk/Sprite.hpp>
#include <cmath>

void Laser::Draw(smk::Screen& screen) {
  smk::Sprite sprite;

  float dx = end.x - start.x;
  float dy = end.y - start.y;
  float length = std::sqrt(dx * dx + dy * dy);
  float angle = std::atan2(-dy, dx) * 360.0 / 2.0 / M_PI;

  sprite.SetScale(length,2);
  sprite.SetPosition(start.x, start.y);
  sprite.SetRotation(angle);
  sprite.SetColor(smk::Color::Red);
  screen.Draw(sprite);
}

#include "game/InvisibleBlock.hpp"
#include <smk/Window.hpp>
#include <cmath>

float sqr(float x) {
  return x * x;
}

void InvisibleBlock::Draw(smk::Window& window, const Hero& hero) {
  float distance =
      std::sqrt(sqr((hero.geometry.left + hero.geometry.right) / 2 -
                    (geometry.left + geometry.right) / 2) +
                sqr((hero.geometry.top + hero.geometry.bottom) / 2 -
                    (geometry.top + geometry.bottom) / 2));

  float coef = (13000 / distance - 100) / 255.0;
  if (coef > 1.0)
    coef = 1.0;
  else if (coef < 0)
    coef = 0;
  sprite.SetColor(glm::vec4(1.0, 1.0, 1.0, coef));
  window.Draw(sprite);
}

InvisibleBlock::InvisibleBlock(int x, int y, int width, int height) {
  geometry.left = x;
  geometry.top = y;
  geometry.right = x + width - 1;
  geometry.bottom = y + height - 1;
  sprite = smk::Sprite(img_block4);
  sprite.SetPosition(x, y);
  sprite.SetScale(float(width - 1) / 31.0, float(height - 1) / 31.0);
}

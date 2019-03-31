#include "Creeper.hpp"
#include "Resource.hpp"
#include <cstdlib>
#include <smk/Screen.hpp>

Creeper::Creeper(int X, int Y) {
  x = X;
  y = Y;
  sprite.SetTexture(img_creeper);
  t = 0;
  mode = 0;
  t = rand() % 10;
  sprite.SetCenter(8, 16);
  geometry = Rectangle(x - 9, x + 9, y - 15, y - 15);
  xspeed = -2;
}
void Creeper::Draw(smk::Screen& screen) {
  sprite.SetPosition(x, y);

  if (mode == 0) {
    int position[] = {-2, -1, 0, 1, 2, 1, 0, -1};
    sprite.SetPosition(x + position[(t / 2) % 8], y);
    screen.Draw(sprite);
  } else {
    switch (t % 2) {
      case 0:
        sprite.SetColor(glm::vec4(255, 255, 255, 100));
        sprite.SetScale(1, 1);
        screen.Draw(sprite);

        sprite.SetColor(glm::vec4(255, 255, 255, 150));
        sprite.SetScale(1.3, 1.3);
        screen.Draw(sprite);

        sprite.SetScale(1, 1);
        sprite.SetColor(glm::vec4(255, 255, 255, 255));

        break;

      default:
        screen.Draw(sprite);
        break;
    }
  }
}

void Creeper::UpdateGeometry() {
  geometry = Rectangle(x - 9, x + 9, y - 15, y - 15);
}

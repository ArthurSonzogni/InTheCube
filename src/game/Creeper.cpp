#include "game/Creeper.hpp"
#include "game/Resource.hpp"
#include <cstdlib>
#include <smk/Window.hpp>

Creeper::Creeper(int X, int Y) {
  x = X;
  y = Y;
  sprite = smk::Sprite(img_creeper);
  t = 0;
  mode = 0;
  t = rand() % 10;
  sprite.SetCenter(8, 16);
  geometry = Rectangle(x - 9, x + 9, y - 15, y - 15);
  xspeed = -2;
}
void Creeper::Draw(smk::Window& window) {
  sprite.SetPosition(x, y);

  if (mode == 0) {
    int position[] = {-2, -1, 0, 1, 2, 1, 0, -1};
    sprite.SetPosition(x + position[(t / 2) % 8], y);
    window.Draw(sprite);
  } else {
    switch (t % 2) {
      case 0:
        sprite.SetColor(glm::vec4(255, 255, 255, 100));
        sprite.SetScale(1, 1);
        window.Draw(sprite);

        sprite.SetColor(glm::vec4(255, 255, 255, 150));
        sprite.SetScale(1.3, 1.3);
        window.Draw(sprite);

        sprite.SetScale(1, 1);
        sprite.SetColor(glm::vec4(255, 255, 255, 255));

        break;

      default:
        window.Draw(sprite);
        break;
    }
  }
}

void Creeper::UpdateGeometry() {
  geometry = Rectangle(x - 9, x + 9, y - 15, y - 15);
}

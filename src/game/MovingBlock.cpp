#include "MovingBlock.hpp"
#include <smk/Window.hpp>
#include "game/Resource.hpp"

MovingBlock::MovingBlock(int X,
                         int Y,
                         int WIDTH,
                         int HEIGHT,
                         float XSPEED,
                         float YSPEED) {
  sprite = smk::Sprite(img_block3);
  sprite.SetPosition(X, Y);
  geometry.left = X;
  geometry.top = Y;
  geometry.right = X + WIDTH - 1;
  geometry.bottom = Y + HEIGHT - 1;
  x = X;
  y = Y;
  xspeed = XSPEED;
  yspeed = YSPEED;
  width = WIDTH;
  height = HEIGHT;
  sprite.SetScale(1, 1);
  if (WIDTH == 32 and HEIGHT == 32) {
    tiled = false;
  } else if (WIDTH % 32 == 0 and HEIGHT % 32 == 0) {
    tiled = true;
    xtile = WIDTH / 32;
    ytile = HEIGHT / 32;
  } else {
    tiled = false;
    sprite.SetScale(float(WIDTH - 1) / 31.0, float(HEIGHT - 1) / 31.0);
  }
}

void MovingBlock::Draw(smk::Window& window) {
  if (tiled) {
    int x = geometry.left;
    int y = geometry.top;
    int a, b;
    for (a = 0; a < xtile; a++) {
      for (b = 0; b < ytile; b++) {
        sprite.SetPosition(x + 32 * a, y + 32 * b);
        window.Draw(sprite);
      }
    }
  } else
    window.Draw(sprite);
}

void MovingBlock::UpdateGeometry() {
  geometry.left = x;
  geometry.right = x + width - 1;
  geometry.top = y;
  geometry.bottom = y + height - 1;
  sprite.SetPosition(x, y);
}

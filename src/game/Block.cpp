#include "game/Block.hpp"
#include "game/Resource.hpp"
#include <smk/Window.hpp>

Block::Block(int x, int y, int width, int height) {
  drawable = true;
  sprite = smk::Sprite(img_block1);
  sprite.SetPosition(x, y);
  geometry.left = x;
  geometry.top = y;
  geometry.right = x + width - 1;
  geometry.bottom = y + height - 1;
  sprite.SetScale(1, 1);
  if (width == 32 and height == 32) {
    tiled = false;
  } else if (width % 32 == 0 and height % 32 == 0) {
    tiled = true;
    xtile = width / 32;
    ytile = height / 32;
  } else {
    tiled = false;
    sprite.SetScale(float(width - 1) / 31.0, float(height - 1) / 31.0);
  }
}

Block::Block(int x, int y, int width, int height, bool) {
  drawable = false;
  geometry.left = x;
  geometry.top = y;
  geometry.right = x + width - 1;
  geometry.bottom = y + height - 1;
  sprite.SetScale(1, 1);
}

void Block::Draw(smk::Window& window) {
  if (!drawable)
    return;

  int i = 0;
  if (!tiled)
    window.Draw(sprite);

  smk::Sprite sprites[] = {
      smk::Sprite(img_block1),
      smk::Sprite(img_block2),
      smk::Sprite(img_block3),
      smk::Sprite(img_block3),
  };

  int x = geometry.left;
  int y = geometry.top;
  for (int a = 0; a < xtile; a++) {
    for (int b = 0; b < ytile; b++) {
      auto& sprite = sprites[i % 4];
      sprite.SetPosition(x + 32 * a, y + 32 * b);
      window.Draw(sprite);
      ++i;
    }
  }
}

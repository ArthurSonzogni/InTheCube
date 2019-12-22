#include "Block.hpp"
#include "Resource.hpp"
#include <smk/Window.hpp>

Block::Block(int x, int y, int width, int height) {
  drawable = true;
  sprite.SetTexture(img_block1);
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
  int i = 0;

  if (drawable) {
    if (tiled) {
      int x = geometry.left;
      int y = geometry.top;
      int a, b;
      for (a = 0; a < xtile; a++) {
        for (b = 0; b < ytile; b++) {
          sprite.SetPosition(x + 32 * a, y + 32 * b);
          if (i == 0) {
            sprite.SetTexture(img_block1);
            i++;
          } else if (i == 1) {
            sprite.SetTexture(img_block2);
            i++;
          } else if (i == 2) {
            sprite.SetTexture(img_block3);
            i++;
          } else if (i == 3) {
            sprite.SetTexture(img_block3);
            i = 0;
          }

          window.Draw(sprite);
        }
      }
    } else {
      window.Draw(sprite);
    }
  }
}

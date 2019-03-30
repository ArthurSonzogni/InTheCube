#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Forme.hpp"
#include "Sprite.hpp"

class Screen;

class Block {
 public:
  Block(int x, int y, int width, int height);
  Block(int x, int y, int width, int height, bool Drawable);
  virtual ~Block() = default;
  Rectangle geometry;
  Sprite sprite;
  int xtile, ytile;
  bool tiled;
  bool drawable;
  virtual void Draw(Screen& screen);
};

#endif /* BLOCK_HPP */

#ifndef BLOCK_HPP
#define BLOCK_HPP

#include "Forme.hpp"
#include <smk/Sprite.hpp>

namespace smk {
class Screen;
}  // namespace smk

class Block {
 public:
  Block(int x, int y, int width, int height);
  Block(int x, int y, int width, int height, bool Drawable);
  virtual ~Block() = default;
  Rectangle geometry;
  smk::Sprite sprite;
  int xtile, ytile;
  bool tiled;
  bool drawable;
  virtual void Draw(smk::Screen& screen);

  Block(Block&&) = default;
};

#endif /* BLOCK_HPP */

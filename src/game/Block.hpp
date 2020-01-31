#ifndef GAME_BLOCK_HPP
#define GAME_BLOCK_HPP

#include "game/Forme.hpp"
#include <smk/Sprite.hpp>

namespace smk {
class Window;
}  // namespace smk

class Block {
 public:
  Block(int x, int y, int width, int height);
  Block(int x, int y, int width, int height, bool Drawable);
  virtual ~Block() = default;
  Rectangle geometry;
  smk::Sprite sprite;
  int xtile = 0;
  int ytile = 0;
  bool tiled;
  bool drawable;
  virtual void Draw(smk::Window& window);

  Block(Block&&) = default;
};

#endif /* GAME_BLOCK_HPP */

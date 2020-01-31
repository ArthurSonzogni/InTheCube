#ifndef GAME_PINCETTE_HPP
#define GAME_PINCETTE_HPP

#include "game/Resource.hpp"
#include <smk/Sprite.hpp>

namespace smk {
class Window;
}  // namespace smk

class Pincette {
 public:
  Pincette();
  void Step();
  void Draw(smk::Window& window);

 private:
  int step_ = 0;
  smk::Sprite pincetteSprite;
  smk::Sprite heroSprite;
};

#endif /* GAME_PINCETTE_HPP */

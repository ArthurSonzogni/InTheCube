#ifndef PINCETTE_HPP
#define PINCETTE_HPP

#include "Resource.hpp"
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

#endif /* PINCETTE_HPP */

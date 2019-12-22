#ifndef DECORS_HPP
#define DECORS_HPP

#include <smk/Sprite.hpp>

namespace smk {
class Window;
}  // namespace smk

class Decor {
 public:
  smk::Sprite sprite;

  Decor(int X, int Y, int IMG);
  void Draw(smk::Window& window);
};

#endif /* DECORS_HPP */

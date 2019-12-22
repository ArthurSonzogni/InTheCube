#ifndef CLONER_HPP
#define CLONER_HPP

#include <smk/Sprite.hpp>

namespace smk {
class Window;
}  // namespace smk

class Cloner {
 public:
  int xstart, ystart, xend, yend;
  bool enable;
  smk::Sprite sprite;
  Cloner(int Xstart, int Ystart, int Xend, int Yend);
  void Draw(smk::Window& window);
};

#endif /* CLONER_HPP */

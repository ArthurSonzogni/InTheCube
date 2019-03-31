#ifndef CLONER_HPP
#define CLONER_HPP

#include <smk/Sprite.hpp>

namespace smk {
class Screen;
}  // namespace smk

class Cloner {
 public:
  int xstart, ystart, xend, yend;
  bool enable;
  smk::Sprite sprite;
  Cloner(int Xstart, int Ystart, int Xend, int Yend);
  void Draw(smk::Screen& screen);
};

#endif /* CLONER_HPP */

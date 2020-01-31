#ifndef GAME_STATIC_MIRROR_HPP
#define GAME_STATIC_MIRROR_HPP

#include <cmath>
#include "game/Forme.hpp"
#include <smk/Sprite.hpp>

namespace smk {
class Window;
}  // namespace smk

#define DEGTORAD 0.0174532925

class StaticMirror {
 public:
  Line geometry;
  smk::Sprite sprite;
  int xattach, yattach;
  int xcenter, ycenter;
  int angle;
  StaticMirror(int x1, int y1, int x2, int y2, int Xattach, int Yattach);
  void Draw(smk::Window& window);
};

#endif /* GAME_STATIC_MIRROR_HPP */

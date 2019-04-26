#ifndef ARROW_LAUNCHER_HPP
#define ARROW_LAUNCHER_HPP

#include <smk/Sound.hpp>
#include <smk/Sprite.hpp>

namespace smk {
class Screen;
}  // namespace smk

class ArrowLauncher {
 public:
  float x, y;
  smk::Sprite sprite;
  smk::Sound sound;
  float orientation;

  ArrowLauncher(float X, float Y, float Orientation);
  void Draw(smk::Screen& screen);
};

#endif /* ARROW_LAUNCHER_HPP */

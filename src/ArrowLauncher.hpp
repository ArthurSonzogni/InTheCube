#ifndef ARROW_LAUNCHER_HPP
#define ARROW_LAUNCHER_HPP

#include "Sound.hpp"
#include "Sprite.hpp"

class Screen;

class ArrowLauncher {
 public:
  float x, y;
  Sprite sprite;
  Sound sound;
  float orientation;

  ArrowLauncher(float X, float Y, float Orientation);
  void Draw(Screen& screen);
};

#endif /* ARROW_LAUNCHER_HPP */

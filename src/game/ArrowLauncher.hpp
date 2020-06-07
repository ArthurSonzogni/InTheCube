// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_ARROW_LAUNCHER_HPP
#define GAME_ARROW_LAUNCHER_HPP

#include <smk/Sound.hpp>
#include <smk/Sprite.hpp>

namespace smk {
class Window;
}  // namespace smk

class ArrowLauncher {
 public:
  float x, y;
  smk::Sprite sprite;
  smk::Sound sound;
  float orientation;

  ArrowLauncher(float X, float Y, float Orientation);
  void Draw(smk::Window& window);
};

#endif /* GAME_ARROW_LAUNCHER_HPP */

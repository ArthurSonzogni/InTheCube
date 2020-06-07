// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_STATIC_MIRROR_HPP
#define GAME_STATIC_MIRROR_HPP

#include <cmath>
#include <smk/Sprite.hpp>

#include "game/Forme.hpp"

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

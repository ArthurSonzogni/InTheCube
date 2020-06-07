// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_CLONER_HPP
#define GAME_CLONER_HPP

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

#endif /* GAME_CLONER_HPP */

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_DECOR_HPP
#define GAME_DECOR_HPP

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

#endif /* GAME_DECOR_HPP */

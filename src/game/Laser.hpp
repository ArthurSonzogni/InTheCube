// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_LASER_HPP
#define GAME_LASER_HPP

#include <smk/Window.hpp>

struct Laser {
  glm::vec2 start;
  glm::vec2 end;
  void Draw(smk::Window& window);
};

#endif /* end of include guard: GAME_LASER_HPP */

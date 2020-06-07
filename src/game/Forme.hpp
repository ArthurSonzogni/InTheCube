// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_FORME_HPP
#define GAME_FORME_HPP

#include <glm/glm.hpp>

class Rectangle {
 public:
  float left, top, right, bottom;
  Rectangle(float l, float r, float b, float t);
  Rectangle();

  // return the Rectangle shifted, it does't modify the Rectangle
  Rectangle shift(float x, float y) const;
  Rectangle increase(float xinc, float yinc) const;
  bool operator==(Rectangle r) const;
};

using Point = glm::vec2;

struct Line {
  glm::vec2 a;
  glm::vec2 b;
};

#endif /* GAME_FORME_HPP */

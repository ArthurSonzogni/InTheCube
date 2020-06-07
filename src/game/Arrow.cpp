// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "game/Arrow.hpp"

#include <cmath>
#include <smk/Window.hpp>

#include "game/Resource.hpp"

Arrow::Arrow(glm::vec2 position, glm::vec2 speed)
    : position(position), speed(speed) {
  sprite = smk::Sprite(img_arrow);
  sprite.SetRotation(std::atan2(-speed.y, speed.x) * 57.3);
  sprite.SetCenter(24, 8);
  damage = false;
  alpha = 255;
}

void Arrow::Step() {
  position += speed;
}

void Arrow::Draw(smk::Window& window) {
  sprite.SetPosition(position);
  sprite.SetColor(glm::vec4(1.f, 1.f, 1.f, alpha / 255.f));
  window.Draw(sprite);
}

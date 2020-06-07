// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "game/StaticMirror.hpp"

#include <smk/Color.hpp>
#include <smk/Shape.hpp>
#include <smk/Window.hpp>

#include "game/Resource.hpp"

StaticMirror::StaticMirror(int x1,
                           int y1,
                           int x2,
                           int y2,
                           int Xattach,
                           int Yattach) {
  float Angle = atan2(y1 - y2, x2 - x1);
  angle = int(Angle / DEGTORAD);

  geometry = {{x1, y1}, {x2, y2}};

  xattach = Xattach;
  yattach = Yattach;

  xcenter = (x1 + x2) / 2;
  ycenter = (y1 + y2) / 2;

  sprite = smk::Sprite(img_miroir);
  sprite.SetPosition(x1, y1);
  sprite.SetCenter(0, 4);
  sprite.SetRotation(angle);
  sprite.SetScaleX(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) / 32.0);
}

void StaticMirror::Draw(smk::Window& window) {
  auto line = smk::Shape::Line({xcenter, ycenter}, {xattach, yattach}, 2);
  line.SetColor(smk::Color::Black);
  window.Draw(line);
  window.Draw(sprite);
}

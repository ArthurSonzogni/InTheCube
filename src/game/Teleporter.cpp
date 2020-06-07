// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "game/Teleporter.hpp"

Teleporter::Teleporter(int X,
                       int Y,
                       int Width,
                       int Height,
                       int XTeleport,
                       int YTeleport) {
  xTeleport = XTeleport;
  yTeleport = YTeleport;
  geometry.left = X;
  geometry.top = Y;
  geometry.right = X + Width - 1;
  geometry.bottom = Y + Height - 1;
}

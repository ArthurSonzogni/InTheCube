// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_TELEPORTER_HPP
#define GAME_TELEPORTER_HPP

#include "game/Forme.hpp"

class Teleporter {
 public:
  Rectangle geometry;
  int xTeleport, yTeleport;

  Teleporter(int X, int Y, int Width, int Height, int XTeleport, int YTeleport);
};

#endif /* GAME_TELEPORTER_HPP */

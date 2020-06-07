// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_ARROW_LAUNCHER_DETECTOR_HPP
#define GAME_ARROW_LAUNCHER_DETECTOR_HPP

#include "game/Forme.hpp"

struct ArrowLauncherDetector {
  Rectangle geometry;
  int launcherID;
  ArrowLauncherDetector(int l, int r, int t, int b, int Mode, int LauncherID);
  int mode;  // 0=single shoot, 1=one soot every second
  int t;
};

#endif /* GAME_ARROW_LAUNCHER_DETECTOR_HPP */

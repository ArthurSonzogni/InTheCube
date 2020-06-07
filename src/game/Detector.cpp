// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "game/Detector.hpp"

Detector::Detector(int x1, int y1, int x2, int y2) {
  geometry.left = x1;
  geometry.right = x2;
  geometry.top = y1;
  geometry.bottom = y2;
}

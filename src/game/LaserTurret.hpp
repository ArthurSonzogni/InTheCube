// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_LASER_TURRET_HPP
#define GAME_LASER_TURRET_HPP

#include <smk/Sprite.hpp>
namespace smk {
class Window;
}  // namespace smk

class LaserTurret {
 public:
  int x, y, angle, xattach, yattach;
  int mode;  // 0-> fixe, 1-> constant rotation, 2-> sinusoidale
  int angleSpeed;
  int angleIncrement;  // used when mode=2
  int angleMedium;     // used when mode=2
  smk::Sprite sprite;
  LaserTurret(int X,
              int Y,
              int Angle,
              int Xattach,
              int Yattach,
              int Mode,
              int AngleSpeed);
  void Draw(smk::Window& window);
  void Step();
};

#endif /* GAME_LASER_TURRET_HPP */

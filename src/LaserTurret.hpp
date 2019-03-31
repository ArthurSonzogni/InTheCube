#ifndef LASER_TURRET_HPP
#define LASER_TURRET_HPP

#include <smk/Sprite.hpp>
namespace smk {
class Screen;
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
  void Draw(smk::Screen& screen);
  void UpdateAngle();
};

#endif /* LASER_TURRET_HPP */

#include "LaserTurret.hpp"

#include <cmath>
#include "Resource.hpp"
#include <smk/Screen.hpp>
#include <smk/Shape.hpp>

LaserTurret::LaserTurret(int X,
                         int Y,
                         int Angle,
                         int Xattach,
                         int Yattach,
                         int Mode,
                         int AngleSpeed) {
  x = X;
  y = Y;
  angle = Angle;
  xattach = Xattach;
  yattach = Yattach;
  mode = Mode;
  angleSpeed = AngleSpeed;
  angleIncrement = 0;

  sprite.SetTexture(img_turret);
  sprite.SetCenter(10, 3);
  sprite.SetRotation(angle);
  sprite.SetPosition(x, y);

  if (mode == 2)
    angleMedium = Angle;
}

void LaserTurret::Draw(smk::Screen& screen) {
  smk::Shape line =
      smk::Shape::Line(x, y, xattach, yattach, 3, glm::vec4(0.0, 0.0, 0.0, 0.0));
  screen.Draw(line);
  screen.Draw(sprite);
}

void LaserTurret::UpdateAngle() {
  switch (mode) {
    case 0:
      break;
    case 1:
      angle += angleSpeed;
      sprite.SetRotation(angle);
      break;
    case 2:
      angleIncrement += angleSpeed;
      angle = angleMedium + 45 * std::sin(angleIncrement * 0.0174532925);
      sprite.SetRotation(angle);
      break;
  }
}

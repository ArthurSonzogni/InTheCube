#include "StaticMirror.hpp"
#include "Resource.hpp"
#include <smk/Screen.hpp>
#include <smk/Shape.hpp>
#include <smk/Color.hpp>

StaticMirror::StaticMirror(int x1,
                           int y1,
                           int x2,
                           int y2,
                           int Xattach,
                           int Yattach) {
  float Angle = atan2(y1 - y2, x2 - x1);
  angle = int(Angle / DEGTORAD);

  geometry.set(x1, y1, x2, y2);

  xattach = Xattach;
  yattach = Yattach;

  xcenter = (x1 + x2) / 2;
  ycenter = (y1 + y2) / 2;

  sprite.SetPosition(x1, y1);
  sprite.SetCenter(0, 4);
  sprite.SetTexture(img_miroir);
  sprite.SetRotation(angle);
  sprite.SetScaleX(sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) / 32.0);
}

void StaticMirror::Draw(smk::Screen& screen) {
  smk::Shape line = smk::Shape::Line({xcenter, ycenter}, {xattach, yattach}, 2);
  line.SetColor(smk::Color::Black);
  screen.Draw(line);
  screen.Draw(sprite);
}

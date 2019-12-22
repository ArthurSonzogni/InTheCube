#include "Electricity.hpp"
#include "Resource.hpp"
#include <smk/Sprite.hpp>
#include <smk/Shape.hpp>

Electricity::Electricity(int X1,
                         int Y1,
                         int X2,
                         int Y2,
                         float Ratio,
                         int Periode,
                         int Offset) {
  sound.SetBuffer(SB_electricity);
  sound.SetLoop(true);
  x1 = X1;
  y1 = Y1;
  x2 = X2;
  y2 = Y2;
  ratio = Ratio;
  periode = Periode;
  offset = Offset;
}

void Electricity::Step(int time) {
  if (((time + offset) % (periode)) < ratio * periode) {
    if (!is_active_) {
      sound.Play();
      is_active_ = true;
    }
  } else {
    if (is_active_) {
      sound.Stop();
      is_active_ = false;
    }
  }
}

void Electricity::Draw(smk::Window& window) {
  smk::Sprite sprite;
  sprite.SetTexture(img_electricitySupport);
  sprite.SetPosition(x1 - 8, y1 - 8);
  window.Draw(sprite);
  sprite.SetPosition(x2 - 8, y2 - 8);
  window.Draw(sprite);

  if (!is_active_)
    return;

  for (int i = 0; i < 3; ++i) {
    int x = x1;
    int y = y1;
    int xfinal = x2;
    int yfinal = y2;
    while (abs(x - xfinal) + abs(y - yfinal) > 5) {
      float angle = atan2(yfinal - y, xfinal - x);
      angle += float(rand() % 10 - 20) * 0.2;
      int xx = x - 9 * cos(angle);
      int yy = y - 9 * sin(angle);
      for (int r = 3; r <= 10; r += 2) {
        auto line1 = smk::Shape::Line({x, y}, {xx, yy}, r);
        line1.SetColor(glm::vec4(242, 224, 58, 20 - r) / 255.f);
        line1.SetBlendMode(smk::BlendMode::Add);
        window.Draw(line1);
      }

      auto line = smk::Shape::Line({x, y}, {xx, yy}, 1);
      line.SetColor(glm::vec4(252, 234, 68, 255) / 255.f);
      x = xx;
      y = yy;

      window.Draw(line);
    }
  }
}

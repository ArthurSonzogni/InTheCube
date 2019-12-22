#include "Laser.hpp"
#include <cmath>
#include <smk/Color.hpp>
#include <smk/Shape.hpp>

void Laser::Draw(smk::Window& window) {
  glm::vec4 color  = smk::Color::Red;
  auto line = smk::Shape::Line(start, end, 1.5f);
  line.SetColor(color);
  window.Draw(line);

  line = smk::Shape::Line(start, end, 2.f);
  color.a = 0.3;
  line.SetColor(color);
  line.SetBlendMode(smk::BlendMode::Add);
  window.Draw(line);

  line = smk::Shape::Line(start, end, 20.f);
  color.a = 0.05;
  line.SetColor(color);
  line.SetBlendMode(smk::BlendMode::Add);
  window.Draw(line);

  line = smk::Shape::Line(start, end, 30.f);
  color.a = 0.02;
  line.SetColor(color);
  line.SetBlendMode(smk::BlendMode::Add);
  window.Draw(line);

  // Draw an halo on the impact of the Laser
  auto circle = smk::Shape::Circle(1.0, 12);
  circle.SetBlendMode(smk::BlendMode::Add);
  circle.SetPosition(end);
  int i = rand();
  for (int r = 1; r <= 12 + i % 5; r += 1) {
    circle.SetScale(r, r);
    circle.SetColor(glm::vec4(0.05, 0, 0, 1.0));
    window.Draw(circle);
  }

}

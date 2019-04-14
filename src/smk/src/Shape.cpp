#include <smk/Shape.hpp>
#include <smk/Shape.hpp>

namespace smk {

Shape Shape::Rectangle(float left,
                       float top,
                       float right,
                       float bottom,
                       glm::vec4 color,
                       float thickness,
                       glm::vec4 borderColor) {
  Shape sprite;
  sprite.SetPosition(left, top);
  sprite.SetScale(right-left, bottom - top);
  sprite.SetColor(color);
  return sprite;
}

Shape Shape::Line(float x1,
                  float y1,
                  float x2,
                  float y2,
                  float thick,
                  glm::vec4 color,
                  float border,
                  glm::vec4 borderColor) {
  return Shape();
}
Shape Shape::Circle(float x, float y, float radius, glm::vec4 color) {
  return Shape();
}

} // namespace smk

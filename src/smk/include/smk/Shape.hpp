#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Drawable.hpp"
#include <smk/Drawable.hpp>

namespace smk {

class Shape : public Drawable {
 public:
  Shape();  // Invalid shape.
  Shape(VertexArray vertex_array);
  ~Shape() override = default;
  Shape(const Shape&) = delete;
  Shape(Shape&&);
  void operator=(const Shape&) = delete;
  void operator=(Shape&&);

  static Shape Line(glm::vec2 a, glm::vec2 b, float thickness);
  static Shape Square();
  static Shape Circle(int subdivisions);

  void Draw(Screen&, RenderState) const override;

 private:
  VertexArray vertex_array_;
};

} // namespace smk

#endif /* end of include guard: SHAPE_HPP */

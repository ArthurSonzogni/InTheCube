#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Drawable.hpp"
#include "Sprite.hpp"

class Shape : public Sprite {
 public:
  static Shape Rectangle(float x,
                         float y,
                         float width,
                         float height,
                         glm::vec4 color,
                         float thickness = 0,
                         glm::vec4 borderColor = {0.0, 0.0, 0.0, 1.0});
  static Shape Line(float x1,
                    float y1,
                    float x2,
                    float y2,
                    float thick,
                    glm::vec4 color,
                    float thickness = 0,
                    glm::vec4 borderColor = {0.0, 0.0, 0.0, 1.0});
  static Shape Circle(float x, float y, float radius, glm::vec4 color);
};

#endif /* end of include guard: SHAPE_HPP */

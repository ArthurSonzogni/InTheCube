#ifndef LASER_H
#define LASER_H

#include <smk/Window.hpp>

struct Laser {
  glm::vec2 start;
  glm::vec2 end;
  void Draw(smk::Window& window);
};

#endif /* end of include guard: LASER_H */

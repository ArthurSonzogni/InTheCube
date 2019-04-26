#ifndef LASER_H
#define LASER_H

#include <smk/Screen.hpp>

struct Laser {
  glm::vec2 start;
  glm::vec2 end;
  void Draw(smk::Screen& screen);
};

#endif /* end of include guard: LASER_H */

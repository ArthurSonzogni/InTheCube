#ifndef LASER_H
#define LASER_H

#include "Forme.hpp"
#include <smk/Screen.hpp>

struct Laser {
  Point start;
  Point end;
  void Draw(smk::Screen& screen);
};

#endif /* end of include guard: LASER_H */

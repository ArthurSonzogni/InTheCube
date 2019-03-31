#ifndef ELECTRICITY_HP
#define ELECTRICITY_HP

#include "Resource.hpp"
#include <smk/Sound.hpp>

class Electricity {
 public:
  int x1, y1, x2, y2;
  float ratio;
  int periode;
  int offset;
  smk::Sound sound;
  bool isSound;
  Electricity(int X1,
              int Y1,
              int X2,
              int Y2,
              float Ratio,
              int Periode,
              int Offset);
};

#endif /* ELECTRICITY_HP */

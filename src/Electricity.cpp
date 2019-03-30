#include "Electricity.hpp"

Electricity::Electricity(int X1,
                         int Y1,
                         int X2,
                         int Y2,
                         float Ratio,
                         int Periode,
                         int Offset) {
  //sound.SetBuffer(SB_electricity);
  //sound.SetLoop(true);
  isSound = false;
  x1 = X1;
  y1 = Y1;
  x2 = X2;
  y2 = Y2;
  ratio = Ratio;
  periode = Periode;
  offset = Offset;
}

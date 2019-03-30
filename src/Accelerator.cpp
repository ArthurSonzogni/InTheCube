#include "Accelerator.hpp"

Accelerator::Accelerator(float x1,
                         float y1,
                         float x2,
                         float y2,
                         float Xacc,
                         float Yacc,
                         float Viscosite) {
  geometry.left = x1;
  geometry.right = x2;
  geometry.top = y1;
  geometry.bottom = y2;
  xacc = Xacc;
  yacc = Yacc;
  viscosite = Viscosite;
}

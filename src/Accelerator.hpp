#ifndef ACCELERATOR_HPP
#define ACCELERATOR_HPP

#include "Forme.hpp"

struct Accelerator {
  float xacc, yacc;
  float viscosite;
  Rectangle geometry;
  Accelerator(float x1,
              float y1,
              float x2,
              float y2,
              float Xacc,
              float Yacc,
              float Viscosite);
};

#endif /* ACCELERATOR_HPP */

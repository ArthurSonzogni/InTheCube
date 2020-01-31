#ifndef GAME_ACCELERATOR_HPP
#define GAME_ACCELERATOR_HPP

#include "game/Forme.hpp"

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

#endif /* GAME_ACCELERATOR_HPP */

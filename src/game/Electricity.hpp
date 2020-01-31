#ifndef GAME_ELECTRICITY_HPP
#define GAME_ELECTRICITY_HPP

#include <smk/Window.hpp>
#include <smk/Sound.hpp>
#include "game/Resource.hpp"

class Electricity {
 public:
  int x1, y1, x2, y2;
  float ratio;
  int periode;
  int offset;
  smk::Sound sound;
  Electricity(int X1,
              int Y1,
              int X2,
              int Y2,
              float Ratio,
              int Periode,
              int Offset);
  void Step(int time);
  void Draw(smk::Window&);
  bool is_active() { return is_active_; }
 private:
  bool is_active_ = false;
};

#endif /* GAME_ELECTRICITY_HPP */

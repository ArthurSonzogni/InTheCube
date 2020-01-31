#ifndef GAME_DETECTOR_HPP
#define GAME_DETECTOR_HPP

#include "game/Forme.hpp"

class Detector {
 public:
  Rectangle geometry;
  bool detected;
  Detector(int x1, int y1, int x2, int y2);
};

#endif /* GAME_DETECTOR_HPP */

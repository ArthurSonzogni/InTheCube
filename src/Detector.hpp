#ifndef DETECTOR_HPP
#define DETECTOR_HPP

#include "Forme.hpp"
#include "Forme.hpp"

class Detector {
 public:
  Rectangle geometry;
  bool detected;
  Detector(int x1, int y1, int x2, int y2);
};

#endif /* DETECTOR_HPP */

#ifndef ARROW_LAUNCHER_DETECTOR_HPP
#define ARROW_LAUNCHER_DETECTOR_HPP

#include "Forme.hpp"

struct ArrowLauncherDetector {
  Rectangle geometry;
  int launcherID;
  ArrowLauncherDetector(int l, int r, int t, int b, int Mode, int LauncherID);
  int mode;  // 0=single shoot, 1=one soot every second
  int t;
};

#endif /* ARROW_LAUNCHER_DETECTOR_HPP */

#include "game/ArrowLauncherDetector.hpp"

ArrowLauncherDetector::ArrowLauncherDetector(int l,
                                             int r,
                                             int T,
                                             int b,
                                             int M,
                                             int LauncherID) {
  geometry.left = l;
  geometry.top = T;
  geometry.right = r;
  geometry.bottom = b;
  mode = M;
  t = 0;
  launcherID = LauncherID;
}

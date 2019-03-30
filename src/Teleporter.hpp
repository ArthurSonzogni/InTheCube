#ifndef TELEPORTER_HPP
#define TELEPORTER_HPP

#include "Forme.hpp"

class Teleporter {
 public:
  Rectangle geometry;
  int xTeleport, yTeleport;

  Teleporter(int X, int Y, int Width, int Height, int XTeleport, int YTeleport);
};

#endif /* TELEPORTER_HPP */

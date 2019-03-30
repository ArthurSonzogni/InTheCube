#ifndef PIC_HPP
#define PIC_HPP

#include "Sprite.hpp"
#include <vector>

class Pic {
 public:
  int x, y, angle;
  int avancement;
  Sprite sprite;

  int nbRequis;
  int comparateur;
  std::vector<int> connexion;

  Pic(int X,
      int Y,
      int Angle,
      int NbRequis,
      int Comparateur,
      std::vector<int> Connexion);
};

#endif /* PIC_HPP */

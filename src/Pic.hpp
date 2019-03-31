#ifndef PIC_HPP
#define PIC_HPP

#include <smk/Sprite.hpp>
#include <vector>

class Pic {
 public:
  int x, y, angle;
  int avancement;
  smk::Sprite sprite;

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

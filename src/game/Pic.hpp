// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#ifndef GAME_PIC_HPP
#define GAME_PIC_HPP

#include <smk/Sprite.hpp>
#include <vector>

namespace smk {
class Window;
}

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

  void Draw(smk::Window& window);
};

#endif /* GAME_PIC_HPP */

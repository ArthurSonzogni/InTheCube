#ifndef SPECIAL_HPP
#define SPECIAL_HPP

#include <list>
#include <smk/Screen.hpp>
#include <smk/Sound.hpp>
#include <smk/Sprite.hpp>
#include <vector>
#include "Arrow.hpp"
#include "ArrowLauncher.hpp"
#include "Particule.hpp"

enum {
  SPECIAL_ARBRE = 0,
  SPECIAL_ARBRE2 = 1,
  SPECIAL_ARBREBOSS = 2,
  SPECIAL_WIND = 3,
  SPECIAL_END = 4,
  SPECIAL_END2 = 5,
  SPECIAL_ACC = 6,
};

class Level;

class Special {
 public:
  int m;
  Special(int M);
  std::vector<int> var;
  std::vector<smk::Sprite> sprite;

  void Step(Level& level);
  void DrawBackground(smk::Screen& screen, float xcenter, float ycenter);
  void DrawOverDecoration(smk::Screen& screen);
  void DrawForeground(smk::Screen& screen, bool& isWin);

  bool erased = false;
};

#endif /* SPECIAL_HPP */

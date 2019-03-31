#ifndef SPECIAL_HPP
#define SPECIAL_HPP

#include <vector>

#include <smk/Sprite.hpp>

#define SPECIAL_ARBRE 0
#define SPECIAL_ARBRE2 1
#define SPECIAL_ARBREBOSS 2
#define SPECIAL_WIND 3
#define SPECIAL_END 4
#define SPECIAL_END2 5
#define SPECIAL_ACC 6

class Special {
 public:
  int m;
  Special(int M);
  std::vector<int> var;
  std::vector<smk::Sprite> sprite;
};

#endif /* SPECIAL_HPP */

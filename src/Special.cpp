#include "Special.hpp"

Special::Special(int M) {
  m = M;
  switch (m) {
    case SPECIAL_ARBRE:
      var.push_back(0);
      var.push_back(0);
      var.push_back(100);
      break;
    case SPECIAL_ARBRE2:
      var.push_back(0);
      var.push_back(100 * 4);
      break;
    case SPECIAL_ARBREBOSS:
      var.push_back(50);  // time before a salvo
      var.push_back(0);   // salvo id
      var.push_back(0);   // arrow witch is throw
      var.push_back(0);   // time to wait before throwing an arrow.
      break;
    case SPECIAL_WIND:
      break;
    case SPECIAL_END:
      var.push_back(0);
      var.push_back(0);
      var.push_back(60);
      break;
    case SPECIAL_END2:
      var.push_back(0);
      var.push_back(0);
      var.push_back(0);
      var.push_back(0);
      var.push_back(0);
      var.push_back(0);
      break;
    case SPECIAL_ACC:
      var.push_back(0);
      break;
  }
}

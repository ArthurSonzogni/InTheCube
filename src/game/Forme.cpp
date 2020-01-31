#include "game/Forme.hpp"

Rectangle::Rectangle(float l, float r, float b, float t) {
  left = l;
  top = t;
  right = r;
  bottom = b;
}

Rectangle::Rectangle() {
  left = 0;
  right = 32;
  top = 0;
  bottom = 32;
}

Rectangle Rectangle::shift(float x, float y) const {
  return Rectangle(left + x, right + x, top + y, bottom + y);
}

Rectangle Rectangle::increase(float xinc, float yinc) const {
  return Rectangle(left - xinc, right + xinc, bottom + yinc, top - yinc);
}

bool Rectangle::operator==(Rectangle r) const {
  if (left != r.left)
    return false;
  if (right != r.right)
    return false;
  if (top != r.top)
    return false;
  if (bottom != r.bottom)
    return false;

  return true;
}

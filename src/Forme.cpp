#include "Forme.hpp"

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

Rectangle Rectangle::shift(float x, float y) {
  return Rectangle(left + x, right + x, top + y, bottom + y);
}

Rectangle Rectangle::increase(float xinc, float yinc) {
  return Rectangle(left - xinc, right + xinc, bottom + yinc, top - yinc);
}

bool Rectangle::operator==(Rectangle r) {
  if (left != r.left)
    return false;
  else if (right != r.right)
    return false;
  else if (top != r.top)
    return false;
  else if (bottom != r.bottom)
    return false;
  else
    return true;
}

Point::Point(float X, float Y) {
  x = X;
  y = Y;
}

Point::Point() {
  x = 0;
  y = 0;
}

Line::Line(float X1, float Y1, float X2, float Y2) {
  x1 = X1;
  x2 = X2;
  y1 = Y1;
  y2 = Y2;
}

Line::Line() {
  x1 = 0;
  x2 = 0;
  y1 = 0;
  y2 = 0;
}

void Line::set(float X1, float Y1, float X2, float Y2) {
  x1 = X1;
  x2 = X2;
  y1 = Y1;
  y2 = Y2;
}

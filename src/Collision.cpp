#include "Collision.hpp"

bool IsBetween(float a, float b, float c) {
  if (b <= c)
    return (b <= a and a <= c);
  else
    return (c <= a and a <= b);
}

bool IsCrossing(float l1, float r1, float l2, float r2) {
  if (IsBetween(l1, l2, r2))
    return true;
  else if (IsBetween(r1, l2, r2))
    return true;
  else if (IsBetween(l2, l1, r1))
    return true;
  else
    return false;
}

bool IsCollision(Rectangle r1, Rectangle r2) {
  return (IsCrossing(r1.left, r1.right, r2.left, r2.right) and
          IsCrossing(r1.top, r1.bottom, r2.top, r2.bottom));
}

bool IsCollision(Rectangle r, Point p) {
  return (IsBetween(p.x, r.left, r.right) and IsBetween(p.y, r.top, r.bottom));
}

bool IsCollision(Point p, Rectangle r) {
  return IsCollision(r, p);
}

bool IsCollision(Rectangle r, Line l) {
  Line l1(r.left, r.top, r.right, r.top);
  Line l2(r.left, r.top, r.left, r.bottom);
  Line l3(r.right, r.top, r.right, r.bottom);
  Line l4(r.left, r.bottom, r.right, r.bottom);

  if (IsCollision(r, Point(l.x1, l.y1)))
    return true;
  else if (IsCollision(l1, l))
    return true;
  else if (IsCollision(l2, l))
    return true;
  else if (IsCollision(l3, l))
    return true;
  else if (IsCollision(l4, l))
    return true;
  else
    return false;
}

bool IsCollision(Line l, Rectangle r) {
  return IsCollision(r, l);
}

bool IsCollision(Line l1, Line l2) {
  Point a(l1.x1, l1.y1);
  Point b(l1.x2, l1.y2);
  Point c(l2.x1, l2.y1);
  Point d(l2.x2, l2.y2);

  if (Side(a, c, d) * Side(b, c, d) > 0)
    return false;
  else if (Side(c, a, b) * Side(d, a, b) > 0)
    return false;
  else
    return true;
}

int Sign(float x) {
  if (x > 0)
    return 1;
  else if (x < 0)
    return -1;
  else
    return 0;
}

int Side(Point m, Point a, Point b) {
  Point ab(b.x - a.x, b.y - a.y);
  Point am(m.x - a.x, m.y - a.y);
  float vectoriel = ab.x * am.y - am.x * ab.y;
  return Sign(vectoriel);
}

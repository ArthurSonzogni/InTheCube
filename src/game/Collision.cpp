// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.

#include "game/Collision.hpp"

bool IsBetween(float a, float b, float c) {
  return b <= c ? b <= a && a <= c  //
                : c <= a && a <= b;
}

bool IsCrossing(float l1, float r1, float l2, float r2) {
  return IsBetween(l1, l2, r2) ||  //
         IsBetween(r1, l2, r2) ||  //
         IsBetween(l2, l1, r1);    //
}

bool IsCollision(Rectangle r1, Rectangle r2) {
  return IsCrossing(r1.left, r1.right, r2.left, r2.right) &&
         IsCrossing(r1.top, r1.bottom, r2.top, r2.bottom);
}

bool IsCollision(Rectangle r, Point p) {
  return IsBetween(p.x, r.left, r.right) && IsBetween(p.y, r.top, r.bottom);
}

bool IsCollision(Point p, Rectangle r) {
  return IsCollision(r, p);
}

bool IsCollision(Rectangle r, Line l) {
  Line l1 = {{r.left, r.top}, {r.right, r.top}};
  Line l2 = {{r.left, r.top}, {r.left, r.bottom}};
  Line l3 = {{r.right, r.top}, {r.right, r.bottom}};
  Line l4 = {{r.left, r.bottom}, {r.right, r.bottom}};

  return IsCollision(r, l.a) ||  //
         IsCollision(l1, l) ||   //
         IsCollision(l2, l) ||   //
         IsCollision(l3, l) ||   //
         IsCollision(l4, l);     //
}

bool IsCollision(Line l, Rectangle r) {
  return IsCollision(r, l);
}

bool IsCollision(Line l1, Line l2) {
  return Side(l1.a, l2.a, l2.b) * Side(l1.b, l2.a, l2.b) < 0 &&
         Side(l2.a, l1.a, l1.b) * Side(l2.b, l1.a, l1.b) < 0;
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

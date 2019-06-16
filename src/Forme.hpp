#ifndef FORME_HPP
#define FORME_HPP

class Rectangle {
 public:
  float left, top, right, bottom;
  Rectangle(float l, float r, float b, float t);
  Rectangle();

  // return the Rectangle shifted, it does't modify the Rectangle
  Rectangle shift(float x, float y) const;
  Rectangle increase(float xinc, float yinc) const;
  bool operator==(Rectangle r) const;
};

class Point {
 public:
  float x, y;
  Point(float X, float Y);
  Point();
};

class Line {
 public:
  float x1, y1, x2, y2;
  Line(float X1, float Y1, float X2, float Y2);
  Line();
  void set(float X1, float Y1, float X2, float Y2);
};

#endif /* FORME_HPP */

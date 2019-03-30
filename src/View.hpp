#ifndef VIEW_H
#define VIEW_H

class View {
 public:
  void SetCenter(float x, float y);
  void SetSize(float width, float height);

public:
  float x_ = 0;
  float y_ = 0;
  float width_ = 0;
  float height_ = 0;
};

#endif /* end of include guard: VIEW_H */

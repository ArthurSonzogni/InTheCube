#ifndef SMK_VIEW_HPP
#define SMK_VIEW_HPP

namespace smk {

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

}  // namespace smk

#endif /* end of include guard: SMK_VIEW_HPP */

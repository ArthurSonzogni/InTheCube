#include <smk/View.hpp>

namespace smk {

void View::SetCenter(float x, float y) {
  x_ = x;
  y_ = y;
}
void View::SetSize(float width, float height) {
  width_ = width;
  height_ = height;
}

} // namespace smk
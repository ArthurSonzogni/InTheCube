#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <glm/glm.hpp>
#include <smk/OpenGL.hpp>

enum class Blend {
  Add,
};

namespace smk {
  class Texture;

class Drawable {
 public:
  void Move(float move_x, float move_y);
  void Rotate(float rotation);
  void SetCenter(float position_x, float position_y);
  void SetPosition(float position_x, float position_y);
  void SetRotation(float rotation);
  void SetScale(float scale_x, float scale_y);
  void SetScaleX(float scale_x);
  void SetScaleY(float scale_y);
  void SetColor(const glm::vec4& color);
  void SetBlendMode(Blend);
  void SetTexture(const Texture& texture);

  glm::mat4 GetTransformation(float size_x, float size_y) const;
  const glm::vec4& color() const;
  const Texture* texture() const;

 private:
  float rotation_ = 0.f;
  float position_x_ = 0.f;
  float position_y_ = 0.f;
  float center_x_ = 0.f;
  float center_y_ = 0.f;
  float scale_x_ = 1.f;
  float scale_y_ = 1.f;
  glm::vec4 color_ = {1.0, 1.0, 1.0, 1.0};
  const Texture* texture_ = nullptr;
};

} // namespace smk

#endif /* end of include guard: DRAWABLE_HPP */

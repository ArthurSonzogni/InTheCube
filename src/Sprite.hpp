#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Drawable.hpp"
#include "Texture.hpp"

class Sprite : public Drawable {
 public:
  void SetTexture(Texture texture);
  void Draw(const glm::mat4& view) const;
 public:
  Texture texture_;
};

#endif /* end of include guard: SPRITE_HPP */

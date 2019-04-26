#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "Drawable.hpp"
#include <smk/Texture.hpp>
#include <smk/RenderState.hpp>
#include <smk/Screen.hpp>

namespace smk {

class Sprite : public Drawable {
 public:
  ~Sprite() override = default;
  void Draw(Screen& screen, RenderState state) const override;
};

}  // namespace smk

#endif /* end of include guard: SPRITE_HPP */

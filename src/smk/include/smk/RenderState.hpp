#ifndef SMK_RENDER_STATE_HPP
#define SMK_RENDER_STATE_HPP

#include <glm/glm.hpp>
#include <smk/Texture.hpp>
#include <smk/VertexArray.hpp>
#include <smk/BlendMode.hpp>

namespace smk {

struct RenderState {
  const Texture* texture = nullptr;
  const VertexArray* vertex_array = nullptr;
  glm::mat4 view;
  glm::vec4 color;
  BlendMode blend_mode = BlendMode::Transparent;
};

} // namespace smk

#endif /* end of include guard: SMK_RENDER_STATE_HPP */

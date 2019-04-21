#ifndef SMK_VERTEX_HPP
#define SMK_VERTEX_HPP

#include <glm/glm.hpp>

namespace smk {

struct Vertex {
  glm::vec2 space_position;
  glm::vec2 texture_position;
};

} // namespace smk.

#endif /* end of include guard: SMK_VERTEX_HPP */

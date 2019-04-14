#ifndef SMK_TEXTURE_HPP
#define SMK_TEXTURE_HPP

#include <smk/OpenGL.hpp>
#include <string>

namespace smk {

struct Texture {
 public:
  Texture();  // empty texture.
  Texture(const std::string& filename);
  ~Texture();

  void Bind(GLuint active_texture = 0) const;

  GLuint id = 0;
  int width = -1;
  int height = -1;

  Texture(Texture&&);         // Movable object.
  void operator=(Texture&&);  // Movable object.
 private:
  Texture(const Texture&) = delete;         // Non copyable object.
  void operator=(const Texture&) = delete;  // Non copyable object.
};

} // namespace smk

#endif  // SMK_TEXTURE_HPP

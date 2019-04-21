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

  // --- Move only resource ----------------------------------------------------
  Texture(Texture&&);
  Texture(const Texture&) = delete;
  void operator=(Texture&&);
  void operator=(const Texture&) = delete;
  // ---------------------------------------------------------------------------
};

} // namespace smk

#endif  // SMK_TEXTURE_HPP

#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include "OpenGL.hpp"
#include "Texture.hpp"

#include <map>
#include <string>

class TextureManager {
 public:
  ~TextureManager();

  Texture LoadTexture(const std::string& filename);
  void Bind(GLuint tex, GLuint activetexture = 0);

 private:
  std::map<std::string, Texture> textures;
};

#endif  // TEXTURE_MANAGER_HPP

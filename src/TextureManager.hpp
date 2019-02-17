#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include "opengl.hpp"

#include <map>
#include <string>

class TextureManager {
 public:
  ~TextureManager();

  GLuint loadTexture(const std::string& filename);
  GLuint loadTextureArray(const std::string& filename, int tileW, int tileH);
  void getTextureSize(const std::string& filename, int* width, int* height);
  void bind(const std::string& filename, GLuint activetexture = GL_TEXTURE0);
  inline void bind(GLuint tex, GLuint activetexture = 0);

 private:
  struct Texture {
    GLuint id;
    int width, height;
  };
  std::map<std::string, Texture> textures;

};

#endif  // TEXTURE_MANAGER_HPP

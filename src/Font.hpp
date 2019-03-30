#ifndef FONT_H
#define FONT_H

#include "OpenGL.hpp"
#include "Texture.hpp"
#include <glm/glm.hpp>
#include <map>
#include <string>

class Font {
 public:
  Font();
  Font(const std::string& filename, int size);

  struct Character {
    Texture texture;
    glm::ivec2 bearing;  // Offset from baseline to left/top of glyph
    float advance;       // Offset to advance to next glyph
  };
  std::map<GLchar, Character> characters;

  int size = 0;
};

#endif /* end of include guard: FONT_H */
